#ifndef CALIBRATETHREAD_H
#define CALIBRATETHREAD_H
#include "opencv.hpp"

#include <QStringList>
#include <QThread>
#include <QImage>
#include "bitmapdialog.h"
using namespace cv;
using namespace std;


class CalibrateThread : public QThread
{
    enum { DETECTION = 0, CAPTURING = 1, CALIBRATED = 2 };
    enum Pattern { CHESSBOARD, CIRCLES_GRID, ASYMMETRIC_CIRCLES_GRID };
    Q_OBJECT

public:

    explicit CalibrateThread(QObject *parent = 0);

public:

    QStringList imgList;
    QString strFileName;
    int m_width;
    int m_height;
    float m_squaresize;

    //BitmapDialog* bDialog;

protected:
    void run();
signals:
    void appendText(QString str);
    void showBitmap(const QImage &);
    void closeImageWindow();
    void popupErrorInformation(QString str);
public slots:

private:
    void saveCameraParams( const string& filename,
                           Size imageSize, Size boardSize,
                           float squareSize, float aspectRatio, int flags,
                           const Mat& cameraMatrix, const Mat& distCoeffs,
                           const vector<Mat>& rvecs, const vector<Mat>& tvecs,
                           const vector<float>& reprojErrs,
                           const vector<vector<Point2f> >& imagePoints,
                           double totalAvgErr );
    bool runCalibration( vector<vector<Point2f> > imagePoints,
                        Size imageSize, Size boardSize, Pattern patternType,
                        float squareSize, float aspectRatio,
                        int flags, Mat& cameraMatrix, Mat& distCoeffs,
                        vector<Mat>& rvecs, vector<Mat>& tvecs,
                        vector<float>& reprojErrs,
                        double& totalAvgErr);
    void calcChessboardCorners(Size boardSize, float squareSize, vector<Point3f>& corners, Pattern patternType = CHESSBOARD);
    double computeReprojectionErrors(
            const vector<vector<Point3f> >& objectPoints,
            const vector<vector<Point2f> >& imagePoints,
            const vector<Mat>& rvecs, const vector<Mat>& tvecs,
            const Mat& cameraMatrix, const Mat& distCoeffs,
            vector<float>& perViewErrors );

    bool runAndSave(const string& outputFilename,
                    const vector<vector<Point2f> >& imagePoints,
                    Size imageSize, Size boardSize, Pattern patternType, float squareSize,
                    float aspectRatio, int flags, Mat& cameraMatrix,
                    Mat& distCoeffs, bool writeExtrinsics, bool writePoints );
    QImage mat2qimage(const Mat& mat);





    
};

#endif // CALIBRATETHREAD_H
