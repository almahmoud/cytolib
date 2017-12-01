/*
 * compensation.hpp
 *
 *  Created on: Apr 8, 2016
 *      Author: wjiang2
 */

#ifndef INCLUDE_COMPENSATION_HPP_
#define INCLUDE_COMPENSATION_HPP_
#include "transformation.hpp"
class compensation{
public:
	string cid;
	string prefix;
	string suffix;
	string name;
	string comment;// store "Acquisition-defined" when the spillOver matrix is not supplied and cid==-1
	vector<string> marker;
	vector<double> spillOver;
	compensation(){};

	void updateChannels(const CHANNEL_MAP & chnl_map){

		for(vector<string>::iterator it = marker.begin(); it != marker.end(); it++)
		{
			string curName = *it;

			CHANNEL_MAP::const_iterator itChnl = chnl_map.find(curName);
			if(itChnl!=chnl_map.end())
				*it = itChnl->second;
		}
	}
	void convertToPb(pb::COMP & comp_pb){
		comp_pb.set_cid(cid);
		comp_pb.set_name(name);
		comp_pb.set_prefix(prefix);
		comp_pb.set_suffix(suffix);
		comp_pb.set_comment(comment);
		BOOST_FOREACH(vector<double>::value_type & it, spillOver){
			comp_pb.add_spillover(it);
		}
		BOOST_FOREACH(vector<string>::value_type & it, marker){
				comp_pb.add_marker(it);
			}
	}
	compensation(const pb::COMP & comp_pb):cid(comp_pb.cid()),prefix(comp_pb.prefix()),suffix(comp_pb.suffix()),name(comp_pb.name()),comment(comp_pb.comment()){
		for(int i = 0; i < comp_pb.marker_size(); i++)
			marker.push_back(comp_pb.marker(i));
		for(int i = 0; i < comp_pb.spillover_size(); i++)
				spillOver.push_back(comp_pb.spillover(i));
	}
};


#endif /* INCLUDE_COMPENSATION_HPP_ */
