#include <rclcpp/rclcpp.hpp>

#include "reg_of_space_server/reg_of_space_server.hpp"

int main(int argc, char** argv){
	rclcpp::init(argc, argv);

	std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("reg_of_space_server_node");

	reg_of_space_server::RegOfSpaceServer reg_of_space_server(node);

	rclcpp::spin(node);

	return 0;
}