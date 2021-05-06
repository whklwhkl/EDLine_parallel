# ifndef __NDARRAY_CONVERTER_H__
# define __NDARRAY_CONVERTER_H__

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <pybind11/stl.h>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>


// class NDArrayConverter {
// public:
//     // must call this first, or the other routines don't work!
//     static bool init_numpy();
//
//     static bool toMat(PyObject* o, cv::Mat &m);
//     static PyObject* toNDArray(const cv::Mat& mat);
// };

//
// Define the type converter
//

struct buffer_info {
    void *ptr;                      /* Pointer to buffer */
    ssize_t itemsize;               /* Size of one scalar */
    std::string format;             /* Python struct-style format descriptor */
    ssize_t ndim;                   /* Number of dimensions */
    std::vector<ssize_t> shape;     /* Buffer dimensions */
    std::vector<ssize_t> strides;    /* Strides (in bytes) for each index */
};


// namespace pybind11 { namespace detail {

// template <> struct type_caster<cv::Mat> {
// public:
//
//     PYBIND11_TYPE_CASTER(cv::Mat, _("numpy.ndarray"));
//
//     bool load(handle src, bool) {
//         return NDArrayConverter::toMat(src.ptr(), value);
//     }
//
//     static handle cast(const cv::Mat &m, return_value_policy, handle defval) {
//         return handle(NDArrayConverter::toNDArray(m));
//     }
// };
//
//
// }} // namespace pybind11::detail

namespace pybind11 { namespace detail{
template<>
struct type_caster<cv::Mat>{
public:
    PYBIND11_TYPE_CASTER(cv::Mat, _("numpy.ndarray"));

    //! 1. cast numpy.ndarray to cv::Mat
    bool load(handle obj, bool){
        auto b = reinterpret_borrow<array>(obj);
        buffer_info info = b.request();

        //const int ndims = (int)info.ndim;
        int nh = 1;
        int nw = 1;
        int nc = 1;
        int ndims = b.ndim();
        if(ndims == 2){
            nh = info.shape[0];
            nw = info.shape[1];
        } else if(ndims == 3){
            nh = info.shape[0];
            nw = info.shape[1];
            nc = info.shape[2];
        }else{
            char msg[64];
            std::sprintf(msg, "Unsupported dim %d, only support 2d, or 3-d", ndims);
            throw std::logic_error(msg);
            return false;
        }

        int dtype;
        if(info.format == format_descriptor<unsigned char>::format()){
            dtype = CV_8UC(nc);
        }else if (info.format == format_descriptor<int>::format()){
            dtype = CV_32SC(nc);
        }else if (info.format == format_descriptor<float>::format()){
            dtype = CV_32FC(nc);
        }else{
            throw std::logic_error("Unsupported type, only support uchar, int32, float");
            return false;
        }

        value = cv::Mat(nh, nw, dtype, info.ptr);
        return true;
    }

    //! 2. cast cv::Mat to numpy.ndarray
    static handle cast(const cv::Mat& mat, return_value_policy, handle defval){
        CV_UNUSED(defval);

        std::string format = format_descriptor<unsigned char>::format();
        size_t elemsize = sizeof(unsigned char);
        int nw = mat.cols;
        int nh = mat.rows;
        int nc = mat.channels();
        int depth = mat.depth();
        int type = mat.type();
        int dim = (depth == type)? 2 : 3;

        if(depth == CV_8U){
            format = format_descriptor<unsigned char>::format();
            elemsize = sizeof(unsigned char);
        }else if(depth == CV_32S){
            format = format_descriptor<int>::format();
            elemsize = sizeof(int);
        }else if(depth == CV_32F){
            format = format_descriptor<float>::format();
            elemsize = sizeof(float);
        }else{
            throw std::logic_error("Unsupport type, only support uchar, int32, float");
        }

        std::vector<size_t> bufferdim;
        std::vector<size_t> strides;
        if (dim == 2) {
            bufferdim = {(size_t) nh, (size_t) nw};
            strides = {elemsize * (size_t) nw, elemsize};
        } else if (dim == 3) {
            bufferdim = {(size_t) nh, (size_t) nw, (size_t) nc};
            strides = {(size_t) elemsize * nw * nc, (size_t) elemsize * nc, (size_t) elemsize};
        }
        return array(buffer_info( mat.data,  elemsize,  format, dim, bufferdim, strides )).release();
    }
};
}}//! end namespace pybind11::detail

# endif
