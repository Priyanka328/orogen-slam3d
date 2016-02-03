/* Generated from orogen/lib/orogen/templates/tasks/Task.hpp */

#ifndef SLAM3D_POINTCLOUDMAPPER_TASK_HPP
#define SLAM3D_POINTCLOUDMAPPER_TASK_HPP

#include "slam3d/PointcloudMapperBase.hpp"

#include <slam3d/GraphMapper.hpp>
#include <slam3d/PointCloudSensor.hpp>
#include <slam3d/Solver.hpp>

#include <octomap/OcTree.h>

#include <queue>
#include <boost/thread/shared_mutex.hpp>

namespace slam3d
{
	class RockOdometry;
	
	class PointcloudMapper : public PointcloudMapperBase
	{
	friend class PointcloudMapperBase;
	protected:

		// Operations
		virtual bool optimize();
		virtual bool generate_map();
		virtual bool generate_octomap();
		
		// Callbacks
		virtual void scanTransformerCallback(const base::Time &ts, const ::base::samples::Pointcloud &scan_sample);

		// Internal methods
		slam3d::PointCloud::Ptr createFromRockMessage(const base::samples::Pointcloud& cloud);
		void createFromPcl(slam3d::PointCloud::ConstPtr pcl_cloud, base::samples::Pointcloud& base_cloud);
		bool processPointcloud(const base::samples::Pointcloud& cloud);
		void sendRobotPose();
		void sendOdometryDrift();
        void addScanToOctoMap(const VertexObject& scan);
		void buildOcTree(const VertexObjectList& vertices);
		void buildPointcloud(const VertexObjectList& vertices);
	
		// Members
		slam3d::Clock* mClock;
		slam3d::Logger* mLogger;
		slam3d::GraphMapper* mMapper;
		slam3d::PointCloudSensor* mPclSensor;
		slam3d::Solver* mSolver;
		RockOdometry* mOdometry;
		octomap::OcTree* mOcTree;
		boost::shared_mutex mGraphMutex;
		
		base::samples::RigidBodyState mOdometryPose;

		std::string mRobotName;
		std::string mRobotFrame;
		std::string mOdometryFrame;
		std::string mMapFrame;
		
		bool mUseColorsAsViewpoints;
		
		int mScansReceived;
		int mScansAdded;
		int mMapPublishRate;
		
		// Parameters for creation of map-pcl
		double mScanResolution;
		double mMapResolution;
		
		// Parameters for outlier rejection in map-pcl
		double   mMapOutlierRadius;
		unsigned mMapOutlierNeighbors;
		
		std::queue<slam3d::VertexObject> mNewVertices;

	public:
		PointcloudMapper(std::string const& name = "slam3d::PointcloudMapper");
		PointcloudMapper(std::string const& name, RTT::ExecutionEngine* engine);
		~PointcloudMapper();

		bool configureHook();
		bool startHook();
		void updateHook();
		void errorHook();
		void stopHook();
		void cleanupHook();
	};
}

#endif

