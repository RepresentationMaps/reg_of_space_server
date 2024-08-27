#ifndef REG_OF_SPACE_SERVER__REG_OF_SPACE_SERVER_HPP
#define REG_OF_SPACE_SERVER__REG_OF_SPACE_SERVER_HPP

#include <string>
#include <map>
#include <random>

#include <rclcpp/rclcpp.hpp>

#include "reg_of_space_server/srv/reg_of_space.hpp"
#include "reg_of_space_server/srv/remove_reg_of_space.hpp"

namespace reg_of_space_server{
	const std::string CHARACTERS = "abcdefghijklmnopqrstuvwxyz";
	const int ID_LENGTH = 5;

	class RegOfSpaceServer{
		private:
			std::shared_ptr<rclcpp::Node> node_;
			std::shared_ptr<rclcpp::Service<reg_of_space_server::srv::RegOfSpace>> register_service_;
			std::shared_ptr<rclcpp::Service<reg_of_space_server::srv::RemoveRegOfSpace>> remove_service_;

			std::random_device rd_;
			std::shared_ptr<std::mt19937> generator_;
			std::shared_ptr<std::uniform_int_distribution<>> distribution_; 

			std::map<std::string, std::string> region_of_space_register_;

			void registerRegionOfSpace(
				const std::shared_ptr<reg_of_space_server::srv::RegOfSpace::Request> request,
				std::shared_ptr<reg_of_space_server::srv::RegOfSpace::Response> response);
			void removeRegionOfSpace(
				const std::shared_ptr<reg_of_space_server::srv::RemoveRegOfSpace::Request> request,
				std::shared_ptr<reg_of_space_server::srv::RemoveRegOfSpace::Response> response);
		protected:
			std::string generateRegId() const;
			bool findRegId(const std::string & reg_id) const;
		public:
			RegOfSpaceServer(const std::shared_ptr<rclcpp::Node> & node);
	};
} // reg_of_space_server
#endif
