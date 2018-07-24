//
// Created by pidan1231239 on 18-7-14.
//

#ifndef SLAM_LEARN_TRACKER_H
#define SLAM_LEARN_TRACKER_H

#include "common_include.h"
#include "LocalMap.h"
#include "Solver3D2D.h"
#include "Config.h"

namespace sky {

    class Tracker {
    private:
        int minInlierNum;
        double minInlierRatio;
        double minKeyFrameDis;
    protected:
        LocalMap::Ptr localMap;
        Solver3D2D solver3D2D;
    public:
        typedef shared_ptr<Tracker> Ptr;

        Tracker(LocalMap::Ptr localMap, cv::Ptr<cv::DescriptorMatcher> matcher,
                int minInlierNum = Config::get<int>("Tracker.minInlierNum"),
                double keyFrameMinInlierRatio = Config::get<double>("Tracker.minInlierRatio"),
                double minKeyFrameDis = Config::get<double>("Tracker.minKeyFrameDis")
        ) :
                localMap(localMap), solver3D2D(matcher),
                minInlierRatio(keyFrameMinInlierRatio),
                minKeyFrameDis(minKeyFrameDis),
                minInlierNum(minInlierNum) {}

        void step(KeyFrame::Ptr frame);

        bool isKeyFrame(KeyFrame::Ptr frame);


    };

}

#endif //SLAM_LEARN_TRACKER_H
