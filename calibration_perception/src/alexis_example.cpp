///////////////////////////////////////////////////////////////////////////////
// File generated by HDevelop for HALCON/C++ Version 13.0
///////////////////////////////////////////////////////////////////////////////



#ifndef __APPLE__

#  include "HalconCpp.h"
#  include "HDevThread.h"
#  include <vector>


#  if defined(__linux__) && !defined(NO_EXPORT_APP_MAIN)

#    include <X11/Xlib.h>

#  endif
#else
#  ifndef HC_LARGE_IMAGES
#    include <HALCONCpp/HalconCpp.h>
#    include <HALCONCpp/HDevThread.h>
#  else
#    include <HALCONCppxl/HalconCpp.h>
#    include <HALCONCppxl/HDevThread.h>
#  endif
#  include <stdio.h>
#  include <HALCON/HpThread.h>
#  include <CoreFoundation/CFRunLoop.h>
#endif

using namespace HalconCpp;


#ifndef NO_EXPORT_MAIN

// Main procedure
void action() {

  // Local iconic variables
  HObject ho_Image, ho_simImage, ho_simAmp, ho_simDir;
  HObject ho_Edges, ho_addedImage;

  // Local control variables
  HTuple hv_source, hv_pathCalDescr, hv_cameraName;
  HTuple hv_pathRoot, hv_pathImageDir, hv_pathImage, hv_pathCalibration;
  HTuple hv_pathPose, hv_pathError, hv_pathCovariances, hv_pathDeviations;
  HTuple hv_nb, hv_NumImages, hv_start, hv_GoodImages, hv_NumCameras;
  HTuple hv_NumCalibObjects, hv_CalibDataID, hv_img_res_x;
  HTuple hv_img_res_y, hv_alpha, hv_start_thres, hv_delta_thres;
  HTuple hv_min_thres, hv_min_cont_length, hv_min_diam_marks;
  HTuple hv_max_diam_marks, hv_mark_thresh, hv_s_Focus, hv_s_Kappa;
  HTuple hv_camera_type, hv_sensor_size_x, hv_sensor_size_y;
  HTuple hv_s_Sx, hv_s_Sy, hv_start_cam_par, hv_i, hv_Exception;
  HTuple hv_Error, hv_CameraParam, hv_NFinalPose, hv_ParamsDeviations;
  HTuple hv_ParamsCovariances, hv_vis_hdevelop, hv_vis_files;
  HTuple hv_WindowHandle1, hv_Pose, hv_save_filename;

  //2013-2014 Universitaet Bremen - Institute for Artificial Intelligence
  //Authors: Benoit Tankoano, Alexis Maldonado

  //Calibration of the camera *

  //Path of the location of the folder Calibration*
  hv_source = "/home/bennypi/kinect2_hd_inital_calib";

  //Path of the file which contains the description of the calibrate plate *
  hv_pathCalDescr = hv_source + "/caltab_hex_10x11.cpd";

  //Name of the camera
  hv_cameraName = "kinect2_rgb";

  //Path to the pictures
  hv_pathImageDir = hv_source + "/halcon_data/boxy_kinect2_intrinsic_cal/pictures";
  //Prefix name of the images (path/frame001.jpg...) *
  hv_pathImage = hv_pathImageDir + "/frame";

  //Path to save the camera parameter *
  hv_pathCalibration = hv_source + "/results/camera.dat";
  //Path to save a pose of the camera *
  hv_pathPose = hv_source + "/results/ImagePose.dat";
  //Path to save the measure error of the calibration *
  hv_pathError = hv_source + "/results/error.dat";
  //Paths to save the other results *
  hv_pathCovariances = hv_source + "/results/paramCovariances.dat";
  hv_pathDeviations = hv_source + "/results/paramDeviations.dat";


  //Variables *
  //number of images *
  ReadTuple(hv_pathImageDir + "/Nbimages.tup", &hv_nb);
  hv_NumImages = hv_nb;
  //begining of the algorithm *
  hv_start = 1;

  hv_GoodImages = HTuple();

  //set up the calibration object
  hv_NumCameras = 1;
  hv_NumCalibObjects = 1;
  CreateCalibData("calibration_object", hv_NumCameras, hv_NumCalibObjects, &hv_CalibDataID);

  //Set the description of the caltab
  SetCalibDataCalibObject(hv_CalibDataID, 0, hv_pathCalDescr);

  if (0 != (hv_cameraName == HTuple("kinect2_rgb"))) {

    //Kinect-2 RGB is FullHD
    hv_img_res_x = 1920;
    hv_img_res_y = 1080;


    hv_alpha = 0.5;
    hv_start_thres = 160;
    hv_delta_thres = 6;
    hv_min_thres = 6;
    hv_min_cont_length = 10;

    hv_mark_thresh = 90;
    hv_min_diam_marks = 10;
    hv_max_diam_marks = 400;

    //5mm lens
    hv_s_Focus = 0.005;

    //s_Kappa := 0.0
    //camera_type := 'area_scan_division'
    hv_camera_type = "area_scan_polynomial";
    hv_s_Kappa.Clear();
    hv_s_Kappa[0] = 0.0;
    hv_s_Kappa[1] = 0.0;
    hv_s_Kappa[2] = 0.0;
    hv_s_Kappa[3] = 0.0;
    hv_s_Kappa[4] = 0.0;

    hv_sensor_size_x = 0.012;
    hv_sensor_size_y = 0.00675;
    hv_s_Sx = hv_sensor_size_x / hv_img_res_x;
    hv_s_Sy = hv_sensor_size_y / hv_img_res_y;

  }

  //See documentation of set_calib_data_cam_param for this list
  hv_start_cam_par.Clear();
  hv_start_cam_par.Append(hv_camera_type);
  hv_start_cam_par.Append(hv_s_Focus);
  hv_start_cam_par.Append(hv_s_Kappa);
  hv_start_cam_par.Append(hv_s_Sx);
  hv_start_cam_par.Append(hv_s_Sy);
  hv_start_cam_par.Append(hv_img_res_x / 2);
  hv_start_cam_par.Append(hv_img_res_y / 2);
  hv_start_cam_par.Append(hv_img_res_x);
  hv_start_cam_par.Append(hv_img_res_y);

  SetCalibDataCamParam(hv_CalibDataID, 0, "", hv_start_cam_par);


  //read calibration images *


      ReadImage(&ho_Image, "/home/bennypi/xenial_ws/src/rac_rosnodes/caltab_detector/calibration-images-2017-08-09-12-58/17.jpg");


      //find calibration pattern
      //Test both to know if the caltab was found and if the different circles were too *
      try {
        FindCalibObject(ho_Image, hv_CalibDataID, 0, 0, 0, HTuple(), HTuple());
        //find_calib_object (Image, CalibDataID, 0, 0, i, ['gap_tolerance', 'alpha', 'max_diam_marks', 'skip_find_caltab'], [0.9, 0.5, 10, 'false'])

        hv_GoodImages = hv_GoodImages.TupleConcat(0);
        std::cout << "success" << std::endl;
      }
        // catch (Exception)
      catch (HalconCpp::HException &HDevExpDefaultException) {
        std::cout << "exception" << std::endl;
        std::cout << HDevExpDefaultException.ErrorMessage() << std::endl;
        HDevExpDefaultException.ToHTuple(&hv_Exception);
      }


  //Actually do the calibration algorithm
  CalibrateCameras(hv_CalibDataID, &hv_Error);



  //Extract some results from the calibration
  //See halcon-11.0-reference-hdevelop.pdf page 321 for more info on the parameters
  GetCalibData(hv_CalibDataID, "camera", 0, "params", &hv_CameraParam);
  GetCalibData(hv_CalibDataID, "camera", 0, "pose", &hv_NFinalPose);
  GetCalibData(hv_CalibDataID, "camera", 0, "params_deviations", &hv_ParamsDeviations);
  GetCalibData(hv_CalibDataID, "camera", 0, "params_covariances", &hv_ParamsCovariances);

  std::cout << hv_CameraParam.ToString() << std::endl;
  HTuple labels, result;
  GetCalibData(hv_CalibDataID, "camera", 0, "params_labels", &labels);
  std::cout << labels.ToString() << std::endl;

  TupleLastN(hv_CameraParam, 1, &result);
  std::cout << result.ToString() << std::endl;
  std::vector<double> resultsListDouble;
  for (int i = 0; i < result.Length(); i++) {
    resultsListDouble.push_back(result[i].D());
  }
  for (auto i = resultsListDouble.begin(); i != resultsListDouble.end(); ++i){
    std::cout << *i  << std::endl;
  }
}


#ifndef NO_EXPORT_APP_MAIN

#ifdef __APPLE__
// On OS X systems, we must have a CFRunLoop running on the main thread in
// order for the HALCON graphics operators to work correctly, and run the
// action function in a separate thread. A CFRunLoopTimer is used to make sure
// the action function is not called before the CFRunLoop is running.
HTuple      gStartMutex;
H_pthread_t gActionThread;

static void timer_callback(CFRunLoopTimerRef timer, void *info)
{
  UnlockMutex(gStartMutex);
}

static Herror apple_action(void **parameters)
{
  LockMutex(gStartMutex);
  action();
  CFRunLoopStop(CFRunLoopGetMain());
  return H_MSG_OK;
}

static int apple_main(int argc, char *argv[])
{
  Herror                error;
  CFRunLoopTimerRef     Timer;
  CFRunLoopTimerContext TimerContext = { 0, 0, 0, 0, 0 };

  CreateMutex("type","sleep",&gStartMutex);
  LockMutex(gStartMutex);

  error = HpThreadHandleAlloc(&gActionThread);
  if (H_MSG_OK != error)
  {
    fprintf(stderr,"HpThreadHandleAlloc failed: %d\n", error);
    exit(1);
  }

  error = HpThreadCreate(gActionThread,0,apple_action);
  if (H_MSG_OK != error)
  {
    fprintf(stderr,"HpThreadCreate failed: %d\n", error);
    exit(1);
  }

  Timer = CFRunLoopTimerCreate(kCFAllocatorDefault,
                               CFAbsoluteTimeGetCurrent(),0,0,0,
                               timer_callback,&TimerContext);
  if (!Timer)
  {
    fprintf(stderr,"CFRunLoopTimerCreate failed\n");
    exit(1);
  }
  CFRunLoopAddTimer(CFRunLoopGetCurrent(),Timer,kCFRunLoopCommonModes);
  CFRunLoopRun();
  CFRunLoopRemoveTimer(CFRunLoopGetCurrent(),Timer,kCFRunLoopCommonModes);
  CFRelease(Timer);

  error = HpThreadHandleFree(gActionThread);
  if (H_MSG_OK != error)
  {
    fprintf(stderr,"HpThreadHandleFree failed: %d\n", error);
    exit(1);
  }

  ClearMutex(gStartMutex);
  return 0;
}
#endif

int main(int argc, char *argv[]) {
#if defined(_WIN32)
  SetSystem("use_window_thread", "true");
#elif defined(__linux__)
  XInitThreads();
#endif

  // Default settings used in HDevelop (can be omitted)
  int ret = 0;
  SetSystem("width", 512);
  SetSystem("height", 512);

#ifndef __APPLE__
  action();
#else
  ret = apple_main(argc,argv);
#endif
  return ret;
}

#endif


#endif


