
/* ShapesType_subscriber.cxx

A subscription example

This file is derived from code automatically generated by the rtiddsgen
command:

rtiddsgen -language C++ -example <arch> ShapesType.idl

Example subscription of type ShapeTypeExtended automatically generated by
'rtiddsgen'. To test them follow these steps:

(1) Compile this file and the example publication.

(2) Start the subscription with the command
objs/<arch>/ShapesType_subscriber <domain_id> <sample_count>

(3) Start the publication with the command
objs/<arch>/ShapesType_publisher <domain_id> <sample_count>

(4) [Optional] Specify the list of discovery initial peers and
multicast receive addresses via an environment variable or a file
(in the current working directory) called NDDS_DISCOVERY_PEERS.

You can run any number of publishers and subscribers programs, and can
add and remove them dynamically from the domain.

Example:

To run the example application on domain <domain_id>:

On Unix:

objs/<arch>/ShapesType_publisher <domain_id>
objs/<arch>/ShapesType_subscriber <domain_id>

On Windows:

objs\<arch>\ShapesType_publisher <domain_id>
objs\<arch>\ShapesType_subscriber <domain_id>

*/

#include <stdio.h>
#include <stdlib.h>

#include "ShapesType.h"
#include "ShapesTypeSupport.h"
#include "ndds/ndds_cpp.h"

#include "ndds/ndds_namespace_cpp.h"

using namespace DDS;

/* Delete all entities */
static int subscriber_shutdown(
    DomainParticipant *participant)
{
    ReturnCode_t retcode;
    int status = 0;

    if (participant != NULL) {
        retcode = participant->delete_contained_entities();
        if (retcode != RETCODE_OK) {
            printf("delete_contained_entities error %d\n", retcode);
            status = -1;
        }

        retcode = TheParticipantFactory->delete_participant(participant);
        if (retcode != RETCODE_OK) {
            printf("delete_participant error %d\n", retcode);
            status = -1;
        }
    }

    /* RTI Connext provides the finalize_instance() method on
    domain participant factory for people who want to release memory used
    by the participant factory. Uncomment the following block of code for
    clean destruction of the singleton. */
    /*

    retcode = DomainParticipantFactory::finalize_instance();
    if (retcode != RETCODE_OK) {
        printf("finalize_instance error %d\n", retcode);
        status = -1;
    }
    */
    return status;
}

extern "C" int subscriber_main(int domainId, int sample_count)
{
    DomainParticipant *participant = NULL;
    Subscriber *subscriber = NULL;
    Topic *topic = NULL;
    DataReader *reader = NULL;
    ReturnCode_t retcode;
    const char *type_name = NULL;
    int count = 0;
    Duration_t receive_period = {4,0};
    int status = 0;
    struct DDS_Duration_t wait_timeout = {1,500000000};
    DDS_StringSeq parameters(1);
    const char* param_list[] = {"GREEN"};
    DDSContentFilteredTopic *cft = NULL;

    /* To customize the participant QoS, use
    the configuration file USER_QOS_PROFILES.xml */
    participant = TheParticipantFactory->create_participant_with_profile(
        domainId, SHAPETYPE_LIBRARY, SHAPETYPE_PROFILE,
        NULL /* listener */, STATUS_MASK_NONE);
    if (participant == NULL) {
        printf("create_participant error\n");
        subscriber_shutdown(participant);
        return -1;
    }

    /* To customize the subscriber QoS, use
    the configuration file USER_QOS_PROFILES.xml */
    subscriber = participant->create_subscriber_with_profile(
        SHAPETYPE_LIBRARY, SHAPETYPE_PROFILE, NULL /* listener */, STATUS_MASK_NONE);
    if (subscriber == NULL) {
        printf("create_subscriber error\n");
        subscriber_shutdown(participant);
        return -1;
    }

    /* Register the type before creating the topic */
    type_name = ShapeTypeExtendedTypeSupport::get_type_name();
    retcode = ShapeTypeExtendedTypeSupport::register_type(
        participant, type_name);
    if (retcode != RETCODE_OK) {
        printf("register_type error %d\n", retcode);
        subscriber_shutdown(participant);
        return -1;
    }

    /* To customize the topic QoS, use
    the configuration file USER_QOS_PROFILES.xml */
    topic = participant->create_topic(
        "Square",
        type_name, TOPIC_QOS_DEFAULT, NULL /* listener */,
        STATUS_MASK_NONE);
    if (topic == NULL) {
        printf("create_topic error\n");
        subscriber_shutdown(participant);
        return -1;
    }

    parameters.from_array(param_list, 1);

    cft = participant->create_contentfilteredtopic_with_filter(
        "ContentFilteredTopic", topic, "color MATCH %0", parameters,
        DDS_STRINGMATCHFILTER_NAME);
    if (cft == NULL) {
        printf("create_contentfilteredtopic error\n");
        subscriber_shutdown(participant);
        return -1;
    }

    /* To customize the data reader QoS, use
    the configuration file USER_QOS_PROFILES.xml */
    reader = subscriber->create_datareader_with_profile(
        cft, SHAPETYPE_LIBRARY, SHAPETYPE_PROFILE, NULL,
        STATUS_MASK_ALL);
    if (reader == NULL) {
        printf("create_datareader error\n");
        subscriber_shutdown(participant);
        return -1;
    }

    DDSStatusCondition * status_condition = reader->get_statuscondition();
    if (status_condition == NULL) {
      printf("Error getting status condition.\n");
      return -1;
    }

    retcode = status_condition->set_enabled_statuses(DDS_DATA_AVAILABLE_STATUS);
    if (retcode != DDS_RETCODE_OK) {
      printf("Error setting enabled status\n");
      return -1;
    }

    DDSWaitSet * waitset = new DDSWaitSet();

    retcode = waitset->attach_condition(status_condition);
    if (retcode != DDS_RETCODE_OK) {
      printf("Error attaching condition to waitset.\n");
      return -1;
    }

    ShapeTypeExtendedDataReader *ShapeTypeExtended_reader =
          ShapeTypeExtendedDataReader::narrow(reader);

    if (ShapeTypeExtended_reader == NULL) {
      printf("Error narrowing reader.\n");
      return -1;
    }

    /* Main loop */
    for (count=0; (sample_count == 0) || (count < sample_count); ++count) {

      DDSConditionSeq active_conditions_seq;

      retcode = waitset->wait(active_conditions_seq, wait_timeout);

      if (retcode == DDS_RETCODE_TIMEOUT) {
          printf("Wait timed out!! No conditions were triggered.\n");
          continue;
      } else if (retcode != DDS_RETCODE_OK) {
          printf("wait returned error: %d\n", retcode);
          break;
      }

      int active_conditions = active_conditions_seq.length();
      printf("Got %d active conditions\n", active_conditions);

      for (int i = 0; i < active_conditions; ++i) {

          /* Compare with Status Conditions */
          if (active_conditions_seq[i] == status_condition) {
              /* Get the status changes so we can check which status
               * condition triggered. */
              DDS_StatusMask triggeredmask =
                      ShapeTypeExtended_reader->get_status_changes();

              /* Subscription matched */
              if (triggeredmask & DDS_DATA_AVAILABLE_STATUS) {

                ShapeTypeExtendedSeq data_seq;
                SampleInfoSeq info_seq;
                int i;

                retcode = ShapeTypeExtended_reader->take(
                    data_seq, info_seq, LENGTH_UNLIMITED,
                    ANY_SAMPLE_STATE, ANY_VIEW_STATE, ANY_INSTANCE_STATE);

                if (retcode == RETCODE_NO_DATA) {
                    return -1;
                } else if (retcode != RETCODE_OK) {
                    printf("take error %d\n", retcode);
                    return -1;
                }

                for (i = 0; i < data_seq.length(); ++i) {
                    if (info_seq[i].valid_data) {
                        printf("Received data\n");
                        ShapeTypeExtendedTypeSupport::print_data(&data_seq[i]);
                    }
                }

                retcode = ShapeTypeExtended_reader->return_loan(data_seq, info_seq);
                if (retcode != RETCODE_OK) {
                    printf("return loan error %d\n", retcode);
                }

              }
            }
         }
    }

    /* Delete all entities */
    status = subscriber_shutdown(participant);

    return status;
}

int main(int argc, char *argv[])
{
    int domainId = 0;
    int sample_count = 0; /* infinite loop */

    if (argc >= 2) {
        domainId = atoi(argv[1]);
    }
    if (argc >= 3) {
        sample_count = atoi(argv[2]);
    }

    /* Uncomment this to turn on additional logging
    NDDSConfigLogger::get_instance()->
    set_verbosity_by_category(NDDS_CONFIG_LOG_CATEGORY_API,
    NDDS_CONFIG_LOG_VERBOSITY_STATUS_ALL);
    */

    return subscriber_main(domainId, sample_count);
}
