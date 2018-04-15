//
// Created by 40161642 on 15/12/2016.
//
#include <include/detector/RobotDetector.h>
// TODO -> code that finds a robot in the image
// Updates the direction property -> where is the detected object

using namespace cv;
using namespace std;

void RobotDetector::initialize(std::string reference_image_path)
{
    /*Mat image_input, image_gray;
image_input = imread(reference_image_path, IMREAD_COLOR);
assert(image_input != NULL);
cvtColor(image_input, image_gray, CV_BGR2GRAY);
blur(image_gray, image_gray, Size(3,3));
reference_mat = image_gray;
orb = ORB::create();
orb->detectAndCompute(reference_mat, noArray(), kpts1, desc1);*/
}

bool RobotDetector::find(const cv::Mat& mat)
{
    bool found = false;
    // Load in reference image
    /*vector<KeyPoint> kpts2;
Mat mat_gray, desc2, homography;
BFMatcher matcher(NORM_HAMMING);
cvtColor(mat, mat_gray, CV_BGR2GRAY);
blur(mat_gray, mat_gray, Size(3,3));
orb->detectAndCompute(mat_gray, noArray(), kpts2, desc2);
// Found descriptor Points in the frame
if (desc2.data != NULL) {
    vector<vector<DMatch>> nn_matches;
    matcher.knnMatch(desc1, desc2, nn_matches, 2);

    // Find matches between the scene and the object
    vector<KeyPoint> matched1, matched2, inliers1, inliers2;
    std::vector<Point2f> obj, scene;
    // Lowe Ratio test for good features
    for (size_t i = 0; i < nn_matches.size(); i++) {
        DMatch first = nn_matches[i][0];
        float dist1 = nn_matches[i][0].distance;
        float dist2 = nn_matches[i][1].distance;
        if (dist1 < (nn_match_ratio * dist2)) {
            //cout << "Distance1: " << dist1 << " distance2: " << dist2 <<
"\n"; matched1.push_back(kpts1[first.queryIdx]);
            matched2.push_back(kpts2[first.trainIdx]);
            obj.push_back(kpts1[first.queryIdx].pt);
            scene.push_back(kpts2[first.trainIdx].pt);
        }
    }
    if (matched1.size() > 0) {
        vector<DMatch> good_matches;
        homography = findHomography(obj, scene, RANSAC, 2.5f, noArray());
        Mat res;
        std::vector<Point2f> scene_object;
        if (homography.data != NULL)
        {
            for (unsigned i = 0; i < matched1.size(); i++) {
                Mat col = Mat::ones(3, 1, CV_64F);
                col.at<double>(0) = matched1[i].pt.x;
                col.at<double>(1) = matched1[i].pt.y;

                col = homography * col;
                col /= col.at<double>(2);
                double dist = sqrt(pow(col.at<double>(0) - matched2[i].pt.x,
2) + pow(col.at<double>(1) - matched2[i].pt.y, 2)); if (dist <
inlier_threshold) {
                    //cout << "Inline distance: " << dist << endl;
                    int new_i = static_cast<int>(inliers1.size());
                    inliers1.push_back(matched1[i]);
                    inliers2.push_back(matched2[i]);
                    scene_object.push_back(matched2[i].pt);
                    good_matches.push_back(DMatch(new_i, new_i, 0));
                }
            }
            // Found a good enough match
            if (inliers1.size() > 15)
            {
                cout << "inliers size: " << inliers1.size() << "\n";
                Rect bounding_box = boundingRect(scene_object);
                found = true;
                cout << "Found Robot" << "\n";
                /*rectangle(mat_gray, boundingRect(scene_object),
Scalar(0,0,255), 5);
                // Display robot detected
                drawMatches(reference_mat, inliers1, mat_gray, inliers2,
good_matches, res); if (res.cols > 0) { resize(res, res, Size(1024, 768));
                    imshow("res", res);
                }
            }
        }
    }
}*/
    return found;
}

/*double RobotDetector::get_direction() {
    return _direction;
}*/