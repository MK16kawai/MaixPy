#pragma once

#include "maix_image.hpp"
#include "pybind11/pybind11.h"
#include "pybind11/numpy.h"

namespace py = pybind11;

namespace maix::tensor
{
    /**
     * float32 type numpy ndarray object to tensor.Tensor object.
     * @param array numpy array object.
     * @param copy if true, will alloc new buffer and copy data, else will directly use array's data buffer, default true.
     *        Use this arg carefully, when set to false, ther array MUST keep alive until we don't use the return tensor of this func, or will cause program crash.
     * @return tensor.Tensor object.
     * @maixpy maix.tensor.tensor_from_numpy_float32
     */
    tensor::Tensor *tensor_from_numpy_float32(py::array_t<float, py::array::c_style> array, bool copy = true)
    {
        py::buffer_info info = array.request();
        std::vector<int> shape_int;
        for(size_t i=0; i<info.shape.size(); ++i)
        {
            shape_int.push_back((int)info.shape[i]);
        }
        if(copy)
        {
            Tensor *t = new Tensor(shape_int, tensor::FLOAT32);
            memcpy(t->data(), info.ptr, t->size_int() * 4);
            return t;
        }
        Tensor *t = new Tensor(shape_int, tensor::FLOAT32, info.ptr);
        return t;
    }

    /**
     * uint8 type numpy ndarray object to tensor.Tensor object.
     * @param array numpy array object.
     * @param copy if true, will alloc new buffer and copy data, else will directly use array's data buffer, default true.
     *        Use this arg carefully, when set to false, ther array MUST keep alive until we don't use the return tensor of this func, or will cause program crash.
     * @return tensor.Tensor object.
     * @maixpy maix.tensor.tensor_from_numpy_uint8
     */
    tensor::Tensor *tensor_from_numpy_uint8(py::array_t<uint8_t, py::array::c_style> array, bool copy = true)
    {
        py::buffer_info info = array.request();
        std::vector<int> shape_int;
        for(size_t i=0; i<info.shape.size(); ++i)
        {
            shape_int.push_back((int)info.shape[i]);
        }
        if(copy)
        {
            Tensor *t = new Tensor(shape_int, tensor::UINT8);
            memcpy(t->data(), info.ptr, t->size_int());
            return t;
        }
        Tensor *t = new Tensor(shape_int, tensor::UINT8, info.ptr);
        return t;
    }

    /**
     * int8 type numpy ndarray object to tensor.Tensor object.
     * @param array numpy array object.
     * @param copy if true, will alloc new buffer and copy data, else will directly use array's data buffer, default true.
     *        Use this arg carefully, when set to false, ther array MUST keep alive until we don't use the return tensor of this func, or will cause program crash.
     * @return tensor.Tensor object.
     * @maixpy maix.tensor.tensor_from_numpy_int8
     */
    tensor::Tensor *tensor_from_numpy_int8(py::array_t<int8_t, py::array::c_style> array, bool copy = true)
    {
        py::buffer_info info = array.request();
        std::vector<int> shape_int;
        for(size_t i=0; i<info.shape.size(); ++i)
        {
            shape_int.push_back((int)info.shape[i]);
        }
        if(copy)
        {
            Tensor *t = new Tensor(shape_int, tensor::INT8);
            memcpy(t->data(), info.ptr, t->size_int());
            return t;
        }
        Tensor *t = new Tensor(shape_int, tensor::INT8, info.ptr);
        return t;
    }

    /**
     * tensor.Tensor object to float32 type numpy ndarray object.
     * @param t tensor.Tensor object.
     * @param copy Whether alloc new Tensor and copy data or not,
     *        if not copy, array object will directly use arg's data buffer, will faster but change array will affect arg's data, default true.
     * @return numpy array object
     * @maixpy maix.tensor.tensor_to_numpy_float32
     */
    py::array_t<float, py::array::c_style> tensor_to_numpy_float32(tensor::Tensor *t, bool copy = true)
    {
        if(!copy)
        {
            return py::array_t<float, py::array::c_style>(t->shape(), (float*)t->data(), py::cast(t));
        }
        Tensor *new_t = new Tensor(t->shape(), t->dtype());
        *new_t = *t;
        auto capsule = py::capsule(new_t, [](void* ptr) {
            delete reinterpret_cast<tensor::Tensor*>(ptr);
        });
        return py::array_t<float, py::array::c_style>(new_t->shape(), (float*)new_t->data(), capsule);
    }

    /**
     * tensor.Tensor object to int8 type numpy ndarray object.
     * @param t tensor.Tensor object.
     * @param copy Whether alloc new Tensor and copy data or not,
     *        if not copy, array object will directly use arg's data buffer, will faster but change array will affect arg's data, default true.
     * @return numpy array object
     * @maixpy maix.tensor.tensor_to_numpy_uint8
     */
    py::array_t<uint8_t, py::array::c_style> tensor_to_numpy_uint8(tensor::Tensor *t, bool copy = true)
    {
        if(!copy)
        {
            return py::array_t<uint8_t, py::array::c_style>(t->shape(), (uint8_t*)t->data(), py::cast(t));
        }
        Tensor *new_t = new Tensor(t->shape(), t->dtype());
        *new_t = *t;
        auto capsule = py::capsule(new_t, [](void* ptr) {
            delete reinterpret_cast<tensor::Tensor*>(ptr);
        });
        return py::array_t<uint8_t, py::array::c_style>(new_t->shape(), (uint8_t*)new_t->data(), capsule);
    }


    /**
     * tensor.Tensor object to int8 type numpy ndarray object.
     * @param t tensor.Tensor object.
     * @param copy Whether alloc new Tensor and copy data or not,
     *        if not copy, array object will directly use arg's data buffer, will faster but change array will affect arg's data, default true.
     * @return numpy array object
     * @maixpy maix.tensor.tensor_to_numpy_int8
     */
    py::array_t<int8_t, py::array::c_style> tensor_to_numpy_int8(tensor::Tensor *t, bool copy = true)
    {
        if(!copy)
        {
            return py::array_t<int8_t, py::array::c_style>(t->shape(), (int8_t*)t->data(), py::cast(t));
        }
        Tensor *new_t = new Tensor(t->shape(), t->dtype());
        *new_t = *t;
        auto capsule = py::capsule(new_t, [](void* img_ptr) {
            delete reinterpret_cast<tensor::Tensor*>(img_ptr);
        });
        return py::array_t<int8_t, py::array::c_style>(new_t->shape(), (int8_t*)new_t->data(), capsule);
    }
} // namespace maix::image
