
/* ShapesType_publisher.cxx

A publication of data of type ShapeTypeExtended

This file is derived from code automatically generated by the rtiddsgen
command:

rtiddsgen -language C++ -example <arch> ShapesType.idl

Example publication of type ShapeTypeExtended automatically generated by
'rtiddsgen'. To test them follow these steps:

(1) Compile this file and the example subscription.

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

objs/<arch>/ShapesType_publisher <domain_id> o
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
static int publisher_shutdown(
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

    /* RTI Connext provides finalize_instance() method on
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

extern "C" int publisher_main(int domainId, int sample_count)
{
    DomainParticipant *participant = NULL;
    Publisher *publisher = NULL;
    Topic *topic = NULL;
    DataWriter *writer = NULL;
    ShapeTypeExtendedDataWriter * ShapeTypeExtended_writer = NULL;
    ShapeTypeExtended *instance = NULL;
    ReturnCode_t retcode;
    InstanceHandle_t instance_handle = HANDLE_NIL;
    const char *type_name = NULL;
    int count = 0;
    Duration_t send_period = {4,0};
    Duration_t wait_period = {1,0};

    /* To customize participant QoS, use
    the configuration file USER_QOS_PROFILES.xml */
    participant = TheParticipantFactory->create_participant_with_profile(
        domainId, SHAPETYPE_LIBRARY, SHAPETYPE_PROFILE,
        NULL /* listener */, STATUS_MASK_NONE);
    if (participant == NULL) {
        printf("create_participant error\n");
        publisher_shutdown(participant);
        return -1;
    }

    /* To customize publisher QoS, use
    the configuration file USER_QOS_PROFILES.xml */
    publisher = participant->create_publisher_with_profile(
        SHAPETYPE_LIBRARY, SHAPETYPE_PROFILE, NULL /* listener */, STATUS_MASK_NONE);
    if (publisher == NULL) {
        printf("create_publisher error\n");
        publisher_shutdown(participant);
        return -1;
    }

    /* Register type before creating topic */
    type_name = ShapeTypeExtendedTypeSupport::get_type_name();
    retcode = ShapeTypeExtendedTypeSupport::register_type(
        participant, type_name);
    if (retcode != RETCODE_OK) {
        printf("register_type error %d\n", retcode);
        publisher_shutdown(participant);
        return -1;
    }

    /* To customize topic QoS, use
    the configuration file USER_QOS_PROFILES.xml */
    topic = participant->create_topic(
        "Square",
        type_name, TOPIC_QOS_DEFAULT, NULL /* listener */,
        STATUS_MASK_NONE);
    if (topic == NULL) {
        printf("create_topic error\n");
        publisher_shutdown(participant);
        return -1;
    }

    /* To customize data writer QoS, use
    the configuration file USER_QOS_PROFILES.xml */
    writer = publisher->create_datawriter_with_profile(
        topic, SHAPETYPE_LIBRARY, SHAPETYPE_PROFILE, NULL /* listener */,
        STATUS_MASK_NONE);
    if (writer == NULL) {
        printf("create_datawriter error\n");
        publisher_shutdown(participant);
        return -1;
    }
    ShapeTypeExtended_writer = ShapeTypeExtendedDataWriter::narrow(writer);
    if (ShapeTypeExtended_writer == NULL) {
        printf("DataWriter narrow error\n");
        publisher_shutdown(participant);
        return -1;
    }

    /* Create data sample for writing */
    instance = ShapeTypeExtendedTypeSupport::create_data();
    if (instance == NULL) {
        printf("ShapeTypeExtendedTypeSupport::create_data error\n");
        publisher_shutdown(participant);
        return -1;
    }

    /* For a data type that has a key, if the same instance is going to be
    written multiple times, initialize the key here
    and register the keyed instance prior to writing */
    /*
    instance_handle = ShapeTypeExtended_writer->register_instance(*instance);
    */

    DDS_PublicationMatchedStatus status;
    ShapeTypeExtended_writer->get_publication_matched_status(status);

    while (status.current_count == 0) {
      printf("Waiting for reader...\n");
      NDDSUtility::sleep(wait_period);
      ShapeTypeExtended_writer->get_publication_matched_status(status);
    }

    printf("Found reader.\n");

    /* Main loop */
    for (count=0; (sample_count == 0) || (count < sample_count); ++count) {

        printf("Writing ShapeTypeExtended, count %d\n", count);

        /* Modify the data to be sent here */
        sprintf(instance->color,"GREEN");
        instance->shapesize = 30;

        instance->x = count;
        instance->y = count;

        if (count > 300)
        {
            count = 0;
        }

        retcode = ShapeTypeExtended_writer->write(*instance, instance_handle);
        if (retcode != RETCODE_OK) {
            printf("write error %d\n", retcode);
        }

        NDDSUtility::sleep(send_period);
    }

    /*
    retcode = ShapeTypeExtended_writer->unregister_instance(
        *instance, instance_handle);
    if (retcode != RETCODE_OK) {
        printf("unregister instance error %d\n", retcode);
    }
    */

    /* Delete data sample */
    retcode = ShapeTypeExtendedTypeSupport::delete_data(instance);
    if (retcode != RETCODE_OK) {
        printf("ShapeTypeExtendedTypeSupport::delete_data error %d\n", retcode);
    }

    /* Delete all entities */
    return publisher_shutdown(participant);
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

    return publisher_main(domainId, sample_count);
}
