#include "detectorBlob.h"

#define BlobMinThreshold  100
#define BlobMaxThreshold  220
#define BlobMinArea       1
#define BlobMaxArea       100

DetectorBlob::DetectorBlob()
{
    g_param = GlobalParameter::getInstance();
    m_bDetect = false;
    m_confThreshold = 0.3f;
    m_nmsThreshold = 0.2f;
    m_classes_num = 80;
    m_max_num = 1000;
    pDefaultBLOB.thresholdStep = 20;
    pDefaultBLOB.minThreshold = BlobMinThreshold;
    pDefaultBLOB.maxThreshold = BlobMaxThreshold;
    pDefaultBLOB.minRepeatability = 2;
    pDefaultBLOB.minDistBetweenBlobs = 10;
    pDefaultBLOB.filterByColor = true;
    pDefaultBLOB.blobColor = 255;
    pDefaultBLOB.filterByArea = true;
    pDefaultBLOB.minArea = BlobMinArea;
    pDefaultBLOB.maxArea = BlobMaxArea;
    pDefaultBLOB.filterByCircularity = false;
    pDefaultBLOB.minCircularity = 0.9f;
    pDefaultBLOB.maxCircularity = (float)1e37;
    pDefaultBLOB.filterByInertia = false;
    pDefaultBLOB.minInertiaRatio = 0.1f;
    pDefaultBLOB.maxInertiaRatio = (float)1e37;
    pDefaultBLOB.filterByConvexity = false;
    pDefaultBLOB.minConvexity = 0.95f;
    pDefaultBLOB.maxConvexity = (float)1e37;
    m_input_img = NULL;

    m_frameNum =  50;
    m_minLineThreshold = 20;
    m_maxdetectLineNum = 3;

	m_staticNum = 5;
	m_maxdetectStaticNum = 3;

}

DetectorBlob::~DetectorBlob()
{
    close();
}

bool DetectorBlob::init()
{
    return true;
}

void DetectorBlob::close()
{
    stopDetect();
    msleep(20);
}

void DetectorBlob::startDetect()
{
    if (m_bDetect == false)
    {
        m_bDetect = true;
        start(QThread::NormalPriority);
    }
}

void DetectorBlob::stopDetect()
{
    m_bDetect = false;
}

void DetectorBlob::setLineMotionTheshold(int frameNum, int minLineThreshold, int maxdetectLineNum)
{
    if(frameNum >= 50)
    {
        m_frameNum = frameNum;
    }

    if(minLineThreshold > 10)
    {
        m_minLineThreshold= minLineThreshold;
    }

    if(maxdetectLineNum > 0)
    {
        m_maxdetectLineNum = maxdetectLineNum;
    }
}

void DetectorBlob::setStaticTheshold(int frameNum, int staticNum, int maxdetectStaticNum)
{
    if(frameNum >= 50)
    {
        m_frameNum = frameNum;
    }

    if(staticNum > 5)
    {
        m_staticNum= staticNum;
    }

    if(maxdetectStaticNum > 0)
    {
        m_maxdetectStaticNum = maxdetectStaticNum;
    }
}

void DetectorBlob::detect(Mat &frame)
{
    m_mutex.lock();

    Mat frame_det = frame.clone();
    if(frame_det.empty())
    {
        qDebug() << "DetectorBlob::detect frame_det.empty";
        return;
    }

	if (numMat.empty())
	{
		numMat.create(frame_det.size(), CV_8UC1);
		numMat = 0;
	}

    Ptr<Feature2D> b;
    vector<KeyPoint>  keyImg;
    vector<KeyPoint>  keyImg1;
    b = SimpleBlobDetector::create(pDefaultBLOB);

    m_res.boxes.clear();
    m_res.prob.clear();
    if (b.dynamicCast<SimpleBlobDetector>() != NULL)
    {
         Ptr<SimpleBlobDetector> sbd = b.dynamicCast<SimpleBlobDetector>();
         sbd->detect(frame_det, keyImg, Mat());
         listVectorPoints.push_back(keyImg);
         for (vector<KeyPoint>::iterator k = keyImg.begin(); k != keyImg.end(); k++)
         {
             numMat.at<uchar>(k->pt) = numMat.at<uchar>(k->pt)+1;
         }

         if (m_frameNum == listVectorPoints.size())
         {
           if(g_param->trackParam.detect_type == 1)  //detect line Motion
           {
               Mat dstClose;
               Mat element = getStructuringElement(MORPH_RECT, Size(7, 7));
               morphologyEx(numMat*255, dstClose, MORPH_CLOSE, element);
               vector<Vec4i> lines;
               HoughLinesP(dstClose, lines, 2, CV_PI / 90, m_minLineThreshold, m_minLineThreshold, 10);
               //sort by line length
			   int count = lines.size();
			   for (int i = 0; i < count - 1; i++)
			   {
				   for (int j = 0; j < count - 1 - i; ++j)
				   {					   
					   float jjLen = (lines[j][2] - lines[j][0])*(lines[j][2] - lines[j][0]) + (lines[j][3] - lines[j][1])*(lines[j][3] - lines[j][1]);
					   float jj1Len = (lines[j+1][2] - lines[j+1][0])*(lines[j+1][2] - lines[j+1][0]) + (lines[j+1][3] - lines[j+1][1])*(lines[j+1][3] - lines[j+1][1]);
					   if (jjLen < jj1Len)
					   {
						   Vec4i temp = lines[j+1];
						   lines[j+1] = lines[j];
						   lines[j] = temp;
					   }
				   }
			   }


               float dstNum = 0;
               float dstNum1 = 0;
               for (vector<KeyPoint>::iterator k = keyImg.begin(); k != keyImg.end(); k++)
               {
                   float xx = k->pt.x;
                   float yy = k->pt.y;
                   for (size_t i = 0; i < lines.size(); i++)
                   {
                       Vec4i l = lines[i];
                       dstNum = (xx - l[0])*(xx - l[0]) + (yy - l[1])*(yy - l[1]);
                       dstNum1 = (xx - l[2])*(xx - l[2]) + (yy - l[3])*(yy - l[3]);
                       if (dstNum > dstNum1)
                       {
                            dstNum = dstNum1;
                       }

                       if (dstNum < 9.1)
                       {
                           Point centerPos = k->pt;
                           int sizeInt = k->size;
                           if (sizeInt < 1)
                                 sizeInt = 1;
                            Rect  kRect(centerPos.x - sizeInt, centerPos.y - sizeInt, 2 * sizeInt, 2 * sizeInt);
                            m_res.boxes.push_back(kRect);
                            m_res.prob.push_back((l[2]-l[0])*(l[2]-l[0])+(l[3]-l[1])*(l[3]-l[1]));
                        }
                     }
                }

               /// remove redundant data
               count = m_res.boxes.size();
               if(count > m_maxdetectLineNum)
               {
                   m_res.boxes.erase(m_res.boxes.begin() + m_maxdetectLineNum, m_res.boxes.end());
                   m_res.prob.erase(m_res.prob.begin() + m_maxdetectLineNum, m_res.prob.end());
               }

           }
           else  //detect static blob
           {
               for (vector<KeyPoint>::iterator k = keyImg.begin(); k != keyImg.end(); k++)
               {
                   int accNum = numMat.at<uchar>(k->pt);
                    if (accNum > m_staticNum)
                    {
                        Point centerPos = k->pt;
                        int sizeInt = k->size;
                        if (sizeInt < 1)
                              sizeInt = 1;
                         Rect  kRect(centerPos.x - sizeInt, centerPos.y - sizeInt, 2 * sizeInt, 2 * sizeInt);
                         m_res.boxes.push_back(kRect);
                         m_res.prob.push_back(accNum);
                    }
                    //sort by Num
					int count = m_res.prob.size();
					for (int i = 0; i < count - 1; i++)
					{
						for (int j = 0; j < count - 1 - i; ++j)
						{
							if (m_res.prob[j] < m_res.prob[j + 1])
							{
								float t_prob = 0;
								t_prob = m_res.prob[j];
								m_res.prob[j] = m_res.prob[j + 1];
								m_res.prob[j + 1] = t_prob;

								Rect t_box = Rect(0, 0, 0, 0);
								t_box = m_res.boxes[j];
								m_res.boxes[j] = m_res.boxes[j + 1];
								m_res.boxes[j + 1] = t_box;
							}
						}
					}

                   // /// remove redundant data
                    if(count > m_maxdetectStaticNum)
                    {
                        m_res.boxes.erase(m_res.boxes.begin() + m_maxdetectStaticNum, m_res.boxes.end());
                        m_res.prob.erase(m_res.prob.begin() + m_maxdetectStaticNum, m_res.prob.end());
                    }
               }
           }



               //imshow("Detect Show", resShowMat);

                keyImg1 = listVectorPoints.front();
                for (vector<KeyPoint>::iterator k = keyImg1.begin(); k != keyImg1.end(); k++)
                {
                   numMat.at<uchar>(k->pt) = numMat.at<uchar>(k->pt) - 1;
                }
                listVectorPoints.pop_front();
           }

   }

    m_mutex.unlock();
}


void DetectorBlob::getDetectResult(DetectResult &res)
{
    m_mutex.lock();
    res.boxes.clear();
    res.classNamesID.clear();
    res.prob.clear();
    res.classNamesVec.clear();

    res.classNamesID.assign(m_res.classNamesID.begin(), m_res.classNamesID.end());
    res.prob.assign(m_res.prob.begin(), m_res.prob.end());
    res.classNamesVec.assign(m_res.classNamesVec.begin(), m_res.classNamesVec.end());
    res.boxes.assign(m_res.boxes.begin(), m_res.boxes.end());
    m_mutex.unlock();
}

void DetectorBlob::setMaxOutputNum(uint n)
{
    m_max_num = n;
}

void DetectorBlob::run()
{
    double time_profile_counter = 0;
    Mat frame;
    while(m_bDetect == true)
    {
        time_profile_counter = cv::getCPUTickCount();
        if (g_param->imageDetectQueue.isEmpty())
        {
            msleep(1);
            continue;
        }
        frame = g_param->imageDetectQueue.dequeue();
        detect(frame);
        getDetectResult(g_param->yolo_res);
        time_profile_counter = cv::getCPUTickCount() - time_profile_counter;

        if(g_param->trackParam.state == DETECT)
        {
            frame.copyTo(g_param->imageDisplay);
        }
        //frame.copyTo(g_param->imageDisplay);
        //g_param->imageDisplayQueue.enqueue(frame);

        //g_param->debugParam.processFPS = 1000 * (cvGetTickFrequency() * 1000) / time_profile_counter;
    }
    stopDetect();
}

void DetectorBlob::imgConvert(const Mat &img, float *dst)
{
    uchar *data = img.data;
    int h = img.rows;
    int w = img.cols;
    int c = img.channels();

    for(int k= 0; k < c; ++k)
    {
        for(int i = 0; i < h; ++i)
        {
            for(int j = 0; j < w; ++j)
            {
                dst[k*w*h+i*w+j] = data[(i*w + j)*c + k]/255.0;
            }
        }
    }
}


