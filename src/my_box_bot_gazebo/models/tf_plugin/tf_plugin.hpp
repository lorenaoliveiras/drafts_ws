#include <gazebo/common/Plugin.hh>
#include <gazebo/physics/physics.hh>
#include <tf2_ros/transform_broadcaster.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>

namespace provant::gz_plugins{
    
    class tf_plugin : public gazebo::ModelPlugin{

        private:

            std::string ref_frame_name;
            double publish_rate;
            link_reference link_name;
            physics::ModelPtr model;
            gazebo::event::ConnectionPtr _updateConnection;
            std::shared_ptr<tf2_ros::TransformBroadcaster> _broadcaster;

        public:

            tf_plugin();
            void Load(physics::ModelPtr _model, sdf::ElementPtr _sdf);
            void Update(const gazebo::common::UpdateInfo& info);

        }

        GZ_REGISTER_MODEL_PLUGIN(TFPlugin)

}