#include <realdds/services/ros2/ros2getcontrolvalue-response.h>
#include <realdds/services/getcontrolvalue-response-msg.h>
#include <realdds/services/ros2/ros2getcontrolvalue-responsePubSubTypes.h>

#include <realdds/dds-topic.h>
#include <realdds/dds-topic-reader.h>
#include <realdds/dds-utilities.h>

#include <fastdds/dds/subscriber/DataReader.hpp>
#include <fastdds/dds/topic/Topic.hpp>

namespace realdds
{
    namespace services
    {

        /*static*/ std::shared_ptr<dds_topic>
        GetControlValueResponseMsg::create_service(std::shared_ptr<dds_participant> const &participant, char const *topic_name)
        {
            return std::make_shared<dds_topic>(participant,
                                               eprosima::fastdds::dds::TypeSupport(new GetControlValueResponseMsg::type),
                                               topic_name);
        }
    }
}
