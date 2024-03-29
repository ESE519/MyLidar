#include <ros/ros.h>
#include <tf/transform_broadcaster.h>

int main(int argc, char** argv){
  ros::init(argc, argv, "tf_broadcaster");
  ros::NodeHandle n;

  ros::Rate r(1);

  tf::TransformBroadcaster broadcaster;
  tf::TransformBroadcaster broadcaster2;


  while(n.ok()){
    broadcaster.sendTransform(
      tf::StampedTransform(
        tf::Transform(tf::Quaternion(0, 0, 0, 1), tf::Vector3(0.0, 0.0, 0.0)),
        ros::Time::now(),"base_link", "base_laser"));
    broadcaster2.sendTransform(
      tf::StampedTransform(
        tf::Transform(tf::Quaternion(0, 0, 0, 1), tf::Vector3(0.0, 0.0, 22.0)),
        ros::Time::now(),"map", "odom"));

    r.sleep();
  }
}
