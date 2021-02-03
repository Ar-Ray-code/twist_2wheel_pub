#include <ros/ros.h>
#include <string>
#include <geometry_msgs/Twist.h>

class twist2wheels
{
private:
    std::string spd_path;
    std::stringstream epos0_path, epos1_path;

    int spd0_old, spd1_old;
    int spd0, spd1;

    ros::NodeHandle nh_;
    ros::NodeHandle pnh_;
    ros::Subscriber sub_;

    void sub_twist_thread(const geometry_msgs::Twist& msg);

public:
    twist2wheels();
};

twist2wheels::twist2wheels()
{
    spd0_old = 0; spd1_old = 0;

    ros::param::get("~path",spd_path);
    std::cout << spd_path << std::endl; 
    epos0_path << spd_path << "/EPOS0.txt";
    epos1_path << spd_path << "/EPOS1.txt";

    std::cout << epos0_path.str() << " : " << epos1_path.str() << std::endl;

    {
        FILE* f0 = fopen(epos0_path.str().c_str(),"w");
        fputs(std::to_string(spd0_old).c_str(),f0);
        fclose(f0);
        spd0_old = spd0;

        FILE* f1 = fopen(epos1_path.str().c_str(),"w");
        fputs(std::to_string(spd1_old).c_str(),f1);
        fclose(f1);
        spd1_old = spd1;
    }
    sub_ = nh_.subscribe("cmd_vel", 1, &twist2wheels::sub_twist_thread, this);
}

void twist2wheels::sub_twist_thread(const geometry_msgs::Twist& msg)
{
    
    spd0 = 0;   spd1 = 0;
    // x
    spd0 += int(msg.linear.x*1000);
    spd1 -= int(msg.linear.x*1000);
    // y
    spd0 += int(msg.angular.z*1000);
    spd1 += int(msg.angular.z*1000);
    
    if(abs(spd0_old - spd0) || abs(spd1_old - spd1))
    {
        FILE* f0 = fopen(epos0_path.str().c_str(),"w");
        FILE* f1 = fopen(epos1_path.str().c_str(),"w");

        fputs(std::to_string(spd0).c_str(),f0);
        fputs(std::to_string(spd1).c_str(),f1);
        
        fclose(f0); fclose(f1);
        spd0_old = spd0; spd1_old = spd1;
        std::cout << "write.." << std::endl;
    }
}

int main(int argc, char** argv)
{
    ros::init(argc,argv,"EPOS_Twist");
    twist2wheels tw;
    ros::spin();
    return 0;
}