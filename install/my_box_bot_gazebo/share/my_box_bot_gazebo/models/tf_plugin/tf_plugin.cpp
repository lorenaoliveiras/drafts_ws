#include "tf_plugin.hpp"

void provant::gz_plugins::Load(physics::ModelPtr _model, sdf::ElementPtr _sdf){

    if (_sdf->HasElement("link_name")){​
        this->link_name = _sdf->Get<std::string>("link_name"); // converter aqui de std::string para link_reference

    }

    else{

        this->link_name = "empty";

    }​
    if (_sdf->HasElement("ref_frame_name")){
            
        this->ref_frame_name = _sdf->Get<std::string>("ref_frame_name");

    }​
    else{

        this->ref_frame_name = "empty";​
    }

    if (_sdf->HasElement("publish_rate")){​
        this->publish_rate = _sdf->Get<double>("publish_rate");

    }​
    else{

        this->publish_rate = 10.0;​
    }

    this->model = _model;​
    this->link = _model->GetLink(link_name_);
    if(!this->link)
    {
        gzerr() << "A link with the provided name (" << link_name_
                << ") does not exist.\n";
    }

    this->_updateConnection = gazebo::event::Events::ConnectWorldUpdateEnd(
        [this]() { this->Update(); });​
    

    // this->broadcaster_ = std::make_shared<tf2_ros::TransformBroadcaster>(ros_node); 
    // é pra inicializar o nó do ros no sdf por esse plugin?
}​
void provant::gzplugins::Update(const gazebo::common::UpdateInfo& info){

    auto const pose = model_->GetLink(link_name_)->WorldPose();​
    geometry_msgs::msg::TransformStamped transform_msg;

    transform_msg.header.frame_id = reference_frame_;​
    transform_msg.child_frame_id = model_->GetName() + "/" + link_name_;

    transform_msg.transform.translation.x = pose.pos.x;
    transform_msg.transform.translation.y = pose.pos.y;
    transform_msg.transform.translation.z = pose.pos.z;​
    transform_msg.transform.rotation.x = pose.rot.x;
    transform_msg.transform.rotation.y = pose.rot.y;
    transform_msg.transform.rotation.z = pose.rot.z;
    transform_msg.transform.rotation.w = pose.rot.w;

    _broadcaster->sendTransform(transform_msg);


}