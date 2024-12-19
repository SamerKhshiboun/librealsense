#include <realdds/topics/ros2/ros2getcontrolvalue-response.h>
#include <realdds/topics/getcontrolvalue-response-msg.h>
#include <realdds/topics/ros2/ros2getcontrolvalue-responsePubSubTypes.h>

#include <realdds/dds-topic.h>
#include <realdds/dds-topic-reader.h>
#include <realdds/dds-utilities.h>

#include <fastdds/dds/subscriber/DataReader.hpp>
#include <fastdds/dds/topic/Topic.hpp>

namespace realdds
{
    namespace topics
    {

        /*static*/ std::shared_ptr<dds_topic>
        GetControlValueResponseMsg::create_topic(std::shared_ptr<dds_participant> const &participant, char const *topic_name)
        {
            return std::make_shared<dds_topic>(participant,
                                               eprosima::fastdds::dds::TypeSupport(new GetControlValueResponseMsg::type),
                                               topic_name);
        }
    } // namespace topics
} // namespace realdds
