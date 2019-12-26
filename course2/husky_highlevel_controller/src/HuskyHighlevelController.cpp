
#include "husky_highlevel_controller/HuskyHighlevelController.hpp"


namespace husky_highlevel_controller {

HuskyHighlevelController::HuskyHighlevelController(ros::NodeHandle& nh)
    : nodeHandle(nh) {
    // get param from config file
    std::string topic;
    int queue_size;
    if ( !nodeHandle.getParam("subscriber_topic", topic) 
        || !nodeHandle.getParam("queue_size", queue_size) ) 
    {
        ROS_ERROR("Could not find subscriber params!"); 
        ros::requestShutdown();
    }
    // create subscriber
    subscriber = nodeHandle.subscribe(topic, queue_size, 
        &HuskyHighlevelController::LaserCallback, this);
    ROS_INFO("Husk highlevel controller node launched!");
}


/*@brief: ROS topic callback function
 * print out the distance to the closest object
 */
void HuskyHighlevelController::LaserCallback(const sensor_msgs::LaserScan &msg) {
    // typeof(msg.ranges) vector<float>(720)
    auto min_elem = std::min_element(msg.ranges.cbegin(), msg.ranges.cend());
    ROS_INFO_STREAM("Closest distance is " << *min_elem);
}


} /* namespace */
