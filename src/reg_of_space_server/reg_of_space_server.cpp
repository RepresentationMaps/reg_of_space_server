#include <reg_of_space_server/reg_of_space_server.hpp>

namespace reg_of_space_server{
	RegOfSpaceServer::RegOfSpaceServer(const std::shared_ptr<rclcpp::Node> & node){
		node_ = node;

		generator_ = std::make_shared<std::mt19937>(rd_());
		distribution_ = std::make_shared<std::uniform_int_distribution<>>(0, CHARACTERS.size() - 1);

		register_service_ = node_->create_service<reg_of_space_server::srv::RegOfSpace>(
			"register_region_of_space",
			std::bind(&RegOfSpaceServer::registerRegionOfSpace, this, std::placeholders::_1, std::placeholders::_2));
		remove_service_ = node_->create_service<reg_of_space_server::srv::RemoveRegOfSpace>(
			"remove_region_of_space",
			std::bind(&RegOfSpaceServer::removeRegionOfSpace, this, std::placeholders::_1, std::placeholders::_2));
	}

	void RegOfSpaceServer::registerRegionOfSpace(
		const std::shared_ptr<reg_of_space_server::srv::RegOfSpace::Request> request,
		std::shared_ptr<reg_of_space_server::srv::RegOfSpace::Response> response){
		std::vector<std::string> regs_id;

		for (int i = 0; i < request->n_regs; i++){
			std::string reg_id = generateRegId();

			// Check whether the generated reg_id is already in the register
			while (findRegId(reg_id)){
				reg_id = generateRegId();
			}

			// Assign the generated ID to the requesting plugin
			region_of_space_register_[reg_id] = request->plugin_name;
			regs_id.push_back(reg_id);
			// WIP: adding information to the knowledge base
		}

		response->regs_of_space_id = regs_id;
	}

	void RegOfSpaceServer::removeRegionOfSpace(
		const std::shared_ptr<reg_of_space_server::srv::RemoveRegOfSpace::Request> request,
		std::shared_ptr<reg_of_space_server::srv::RemoveRegOfSpace::Response> response){
		response->result = true;
		for (auto& reg_of_space_id: request->regs_of_space_id){
			if (findRegId(reg_of_space_id)){
				region_of_space_register_.erase(reg_of_space_id);
			} else {
				response->result = false;
			}
		}
	}

	bool RegOfSpaceServer::findRegId(const std::string & reg_id) const {
		return (region_of_space_register_.find(reg_id) != region_of_space_register_.end());
	}

	std::string RegOfSpaceServer::generateRegId() const {
		std::string random_string;
	    for (int i = 0; i < ID_LENGTH; ++i) {
	        random_string += CHARACTERS[(*distribution_)((*generator_))];
	    }
	    return random_string;
	}
}