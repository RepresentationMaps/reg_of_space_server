reg_of_space_server
===================
A package implementing a ROS 2 server for the plugins
to request new, unique IDs for the spatially-grounded
instances they want to insert in the knowledge base.
The server also handles the deletion of the instances.

Building
--------

`$ rosdep init`
`$ rosdep update`
`$ rosdep install --from-paths src/simulation_player`
`$ colcon build --packages-select simulation_player`

Usage
-----

`$ ros2 run reg_of_space_server reg_of_space_server_node`

Interfaces
**********

The node exposes the following services:
- `/register_region_of_space` (service, type `reg_of_space_server/srv/RegOfSpace`):
	interface exposed to receive requests for registering new instances.
	The node expects the message to report the number of new regions requested.
	It returns a vector of strings with the requested identifiers.
- `/remove_region_of_space` (service, type `reg_of_space_server/srv/RemoveRegOfSpace`):
	interface exposed to receive requests for removing previously added interfaces.




