// __BEGIN_LICENSE__
//  Copyright (c) 2009-2013, United States Government as represented by the
//  Administrator of the National Aeronautics and Space Administration. All
//  rights reserved.
//
//  The NGT platform is licensed under the Apache License, Version 2.0 (the
//  "License"); you may not use this file except in compliance with the
//  License. You may obtain a copy of the License at
//  http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
// __END_LICENSE__


/// \file StereoSessionPinhole.h
///

#ifndef __STEREO_SESSION_PINHOLE_H__
#define __STEREO_SESSION_PINHOLE_H__

#include <asp/Sessions/StereoSessionConcrete.h>
#include <vw/Stereo/StereoModel.h>

namespace asp {

  class StereoSessionPinhole : public StereoSessionConcrete<DISKTRANSFORM_TYPE_MATRIX_RIGHT, STEREOMODEL_TYPE_PINHOLE>{//StereoSession {
  public:

    virtual ~StereoSessionPinhole() {}
/*
    // Correct lens distortion and epipolar-rectify the images
    virtual boost::shared_ptr<vw::camera::CameraModel>
    camera_model(std::string const& image_file,
                 std::string const& camera_file = "");
*/
    virtual std::string name() const { return "pinhole"; }
/*
    // For reversing our arithmetic applied in preprocessing.
    typedef vw::HomographyTransform tx_type;
    typedef vw::stereo::StereoModel stereo_model_type;
    tx_type tx_left() const;
    tx_type tx_right() const;
*/
    // Specialization for how interest points are found
    virtual bool ip_matching(std::string const& input_file1,
                             std::string const& input_file2,
                             float nodata1, float nodata2,
                             std::string const& match_filename,
                             vw::camera::CameraModel* cam1,
                             vw::camera::CameraModel* cam2);

    // Stage 1: Preprocessing
    //
    // Pre file is a pair of images.            ( ImageView<PixelT> )
    // Post file is a grayscale images.         ( ImageView<PixelGray<float> > )
    virtual void pre_preprocessing_hook(bool adjust_left_image_size,
                                        std::string const& left_input_file,
                                        std::string const& right_input_file,
                                        std::string      & left_output_file,
                                        std::string      & right_output_file);

    static StereoSession* construct() { return new StereoSessionPinhole; }

 private:
    /// Helper function for determining image alignment.
    /// - Only used in pre_preprocessing_hook()
    vw::Matrix3x3 determine_image_align( std::string const& out_prefix,
                                         std::string const& input_file1,
                                         std::string const& input_file2,
                                         float nodata1, float nodata2);
  };

}

#endif // __STEREO_SESSION_PINHOLE_H__
