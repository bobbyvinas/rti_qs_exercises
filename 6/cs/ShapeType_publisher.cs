
/*   
ShapeType_publisher.cs

A publication of data of type ShapeType

This file is derived from code automatically generated by the rtiddsgen 
command:

rtiddsgen -language C# -example <arch> ShapeType.idl

Example publication of type ShapeType automatically generated by 
'rtiddsgen'. To test them follow these steps:

(1) Compile this file and the example subscription.

(2) Start the subscription with the command
objs\<arch>${constructMap.nativeFQNameInModule}_subscriber <domain_id> <sample_count>

(3) Start the publication with the command
objs\<arch>${constructMap.nativeFQNameInModule}_publisher <domain_id> <sample_count>

(4) [Optional] Specify the list of discovery initial peers and 
multicast receive addresses via an environment variable or a file 
(in the current working directory) called NDDS_DISCOVERY_PEERS. 

You can run any number of publishers and subscribers programs, and can 
add and remove them dynamically from the domain.

Example:

To run the example application on domain <domain_id>:

bin\<Debug|Release>\ShapeType_publisher <domain_id> <sample_count>
bin\<Debug|Release>\ShapeType_subscriber <domain_id> <sample_count>
*/

using System;
using System.Collections.Generic;
using System.Text;

public class ShapeTypePublisher {

    public static void Main(string[] args) {

        // --- Get domain ID --- //
        int domain_id = 0;
        if (args.Length >= 1) {
            domain_id = Int32.Parse(args[0]);
        }

        // --- Get max loop count; 0 means infinite loop  --- //
        int sample_count = 0;
        if (args.Length >= 2) {
            sample_count = Int32.Parse(args[1]);
        }

        /* Uncomment this to turn on additional logging
        NDDS.ConfigLogger.get_instance().set_verbosity_by_category(
            NDDS.LogCategory.NDDS_CONFIG_LOG_CATEGORY_API, 
            NDDS.LogVerbosity.NDDS_CONFIG_LOG_VERBOSITY_STATUS_ALL);
        */

        // --- Run --- //
        try {
            ShapeTypePublisher.publish(
                domain_id, sample_count);
        }
        catch(DDS.Exception)
        {
            Console.WriteLine("error in publisher");
        }
    }

    static void publish(int domain_id, int sample_count) {

        // --- Create participant --- //

        /* To customize participant QoS, use 
        the configuration file USER_QOS_PROFILES.xml */
        DDS.DomainParticipant participant =
        DDS.DomainParticipantFactory.get_instance().create_participant_with_profile(
            domain_id,
            SHAPETYPE_LIBRARY.VALUE, SHAPETYPE_PROFILE.VALUE,
            null /* listener */,
            DDS.StatusMask.STATUS_MASK_NONE);
        if (participant == null) {
            shutdown(participant);
            throw new ApplicationException("create_participant error");
        }

        // --- Create publisher --- //

        /* To customize publisher QoS, use 
        the configuration file USER_QOS_PROFILES.xml */
        DDS.Publisher publisher = participant.create_publisher_with_profile(
            SHAPETYPE_LIBRARY.VALUE, SHAPETYPE_PROFILE.VALUE,
            null /* listener */,
            DDS.StatusMask.STATUS_MASK_NONE);
        if (publisher == null) {
            shutdown(participant);
            throw new ApplicationException("create_publisher error");
        }

        // --- Create topic --- //

        /* Register type before creating topic */
        System.String type_name = ShapeTypeTypeSupport.get_type_name();
        try {
            ShapeTypeTypeSupport.register_type(
                participant, type_name);
        }
        catch(DDS.Exception e) {
            Console.WriteLine("register_type error {0}", e);
            shutdown(participant);
            throw e;
        }

        /* To customize topic QoS, use 
        the configuration file USER_QOS_PROFILES.xml */
        DDS.Topic topic = participant.create_topic(
            "Square",
            type_name,
            DDS.DomainParticipant.TOPIC_QOS_DEFAULT,
            null /* listener */,
            DDS.StatusMask.STATUS_MASK_NONE);
        if (topic == null) {
            shutdown(participant);
            throw new ApplicationException("create_topic error");
        }

        // --- Create writer --- //

        /* To customize data writer QoS, use 
        the configuration file USER_QOS_PROFILES.xml */
        DDS.DataWriter writer = publisher.create_datawriter_with_profile(
            topic,
            SHAPETYPE_LIBRARY.VALUE, SHAPETYPE_PROFILE.VALUE,
            null /* listener */,
            DDS.StatusMask.STATUS_MASK_NONE);
        if (writer == null) {
            shutdown(participant);
            throw new ApplicationException("create_datawriter error");
        }
        ShapeTypeDataWriter ShapeType_writer =
        (ShapeTypeDataWriter)writer;

        // --- Write --- //

        /* Create data sample for writing */
        ShapeType instance = ShapeTypeTypeSupport.create_data();
        if (instance == null) {
            shutdown(participant);
            throw new ApplicationException(
                "ShapeTypeTypeSupport.create_data error");
        }

        /* For a data type that has a key, if the same instance is going to be
        written multiple times, initialize the key here
        and register the keyed instance prior to writing */
        DDS.InstanceHandle_t instance_handle = DDS.InstanceHandle_t.HANDLE_NIL;
        /*
        instance_handle = ShapeType_writer.register_instance(instance);
        */

        // Wait for a reader before we publish samples
/*
        DDS.PublicationMatchedStatus status = new DDS.PublicationMatchedStatus();
        const System.Int32 wait_period = 1000; // milliseconds

        while (status.current_count == 0)
        {
            writer.get_publication_matched_status(ref status);
            Console.WriteLine("Waiting for reader...");
            System.Threading.Thread.Sleep(wait_period);
        }

*/

        instance.color = "GREEN";
        instance.shapesize = 30;

        /* Main loop */
        const System.Int32 send_period = 100; // milliseconds
        for (int count=0; (sample_count == 0) || (count < sample_count); ++count) {
            Console.WriteLine("Writing ShapeType, count {0}", count);

            /* Modify the data to be sent here */
            instance.x = count;
            instance.y = count;

            if (count > 300)
            {
                count = 0;
            }

            try {
                ShapeType_writer.write(instance, ref instance_handle);
            }
            catch(DDS.Exception e) {
                Console.WriteLine("write error {0}", e);
            }

            System.Threading.Thread.Sleep(send_period);
        }

        /*
        try {
            ShapeType_writer.unregister_instance(
                instance, ref instance_handle);
        } catch(DDS.Exception e) {
            Console.WriteLine("unregister instance error: {0}", e);
        }
        */

        // --- Shutdown --- //

        /* Delete data sample */
        try {
            ShapeTypeTypeSupport.delete_data(instance);
        } catch(DDS.Exception e) {
            Console.WriteLine(
                "ShapeTypeTypeSupport.delete_data error: {0}", e);
        }

        /* Delete all entities */
        shutdown(participant);
    }

    static void shutdown(
        DDS.DomainParticipant participant) {

        /* Delete all entities */

        if (participant != null) {
            participant.delete_contained_entities();
            DDS.DomainParticipantFactory.get_instance().delete_participant(
                ref participant);
        }

        /* RTI Connext provides finalize_instance() method on
        domain participant factory for people who want to release memory
        used by the participant factory. Uncomment the following block of
        code for clean destruction of the singleton. */
        /*
        try {
            DDS.DomainParticipantFactory.finalize_instance();
        } catch (DDS.Exception e) {
            Console.WriteLine("finalize_instance error: {0}", e);
            throw e;
        }
        */
    }
}

