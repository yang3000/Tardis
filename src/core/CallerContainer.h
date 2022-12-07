#pragma once

#include "Base.h"
#include "Caller.h"
#include "FreeCaller.h"
#include "LamdaCaller.h"
#include "ValueHelper.h"
#include <assert.h>
#include <functional>
#include <memory>
#include <vector>
#include <string>
#include <unordered_map>

namespace TARDIS::CORE
{
    struct ParamInfo
    {
        ParamInfo(
            const std::string &name = "",
            const std::string &desc = "",
            const std::string &type = "",
            const std::string &typeId = "") 
            : m_name(name)
            , m_desc(desc)
            , m_type(type)
            , m_typeId(typeId)
        { }

        std::string m_name;
        std::string m_desc;
        std::string m_type;
        std::string m_typeId;
    };

    struct CallerInfo
    {
        CallerInfo(const char *pName, ICaller *p_caller) 
            : name(pName)
            , caller(p_caller)
        { }

        ~CallerInfo()
        {
            printf("destroy caller:%s\r\n", name.c_str());
            delete caller;
        }

        ICaller *caller;
        std::vector<ParamInfo> params;
        std::string name;
    };

    /***
        实现参数序列化，以
        {
            {"参数名","参数类型","参数描述"},
            {"Imei", "string", "传递要写入的Imei字符串"}
        }
        格式传递到UI，供用户参考。
    ***/
    template <typename... Args>
    struct Parameterized
    {
        typename GenSeq<sizeof...(Args)>::Type m_seq;

        size_t ParamLen = sizeof...(Args);

        Parameterized(std::vector<ParamInfo> &desData, const std::vector<ParamInfo> &srcData) 
            : m_desData(desData)
            , m_srcData(srcData)
        {
            assert(ParamLen <= srcData.size());
            desData.resize(ParamLen);
        }

        template <typename T, int I>
        bool setParam()
        {
            m_desData[I].m_name   = m_srcData[I].m_name;
            m_desData[I].m_desc   = m_srcData[I].m_desc;
            m_desData[I].m_type   = ValueHelper<T>::getDataTypeName();
            m_desData[I].m_typeId = ValueHelper<char>::toString(ValueHelper<T>::Type);
            return true;
        }

        template <int... I>
        void initParams(Seq<I...>) { (setParam<Args, I>(), ...); }

        void operator()() { initParams(m_seq); }

        std::vector<ParamInfo> &m_desData;
        const std::vector<ParamInfo> &m_srcData;
    };

    class CallerContainer final
    {
    public:
        CallerContainer() = default;
        ~CallerContainer();

        // 成员函数绑定
        template <typename T, typename R, typename... Args>
        void registerFunctor(const char *fnName, R (T::*fn)(Args...), T *pObj, const std::vector<ParamInfo> &paramData)
        {
            CallerInfo *t_fndata = new CallerInfo(fnName, new Caller<T, R, Args...>(fn, pObj));
            Parameterized<Args...>(t_fndata->params, paramData)();
            addFunctor(fnName, t_fndata);
        }

        // 自由函数绑定
        template <typename R, typename... Args>
        void registerFunctor(const char *fnName, R (*fn)(Args...), const std::vector<ParamInfo> &paramData)
        {
            CallerInfo *t_fndata = new CallerInfo(fnName, new FreeCaller<R, Args...>(fn));
            Parameterized<Args...>(t_fndata->params, paramData)();
            addFunctor(fnName, t_fndata);
        }

        // std::function函数绑定
        template <typename R, typename... Args>
        void registerFunctor(const char *fnName, std::function<R(Args...)> Fn, const std::vector<ParamInfo> &paramData)
        {
            CallerInfo *t_fndata = new CallerInfo(fnName, new FreeCaller<R, Args...>(Fn));
            Parameterized<Args...>(t_fndata->params, paramData)();
            addFunctor(fnName, t_fndata);
        }

        // lamda表达式绑定
        template <typename FN>
        void registerFunctor(const char *fnName, FN &&fn, const std::vector<ParamInfo> &paramData)
        {
            registerFunctor(fnName, &FN::operator(), std::forward<FN>(fn), paramData);
        }

        // const类型(默认)lamda表达式绑定
        template <typename T, typename R, typename... Args>
        void registerFunctor(const char *fnName, R (T::*)(Args...) const, T &&obj, const std::vector<ParamInfo> &paramData)
        {
            using FnType = std::function<R(Args...)>;
            registerFunctor(fnName, FnType(obj), paramData);
        }

        // mutable lamda表达式绑定
        template <typename T, typename R, typename... Args>
        void registerFunctor(const char *fnName, R (T::*)(Args...), T &&obj, const std::vector<ParamInfo> &paramData)
        {
            using FnType = std::function<R(Args...)>;
            registerFunctor(fnName, FnType(std::forward<T>(obj)), paramData);
        }

        CallerInfo *get(const std::string &name);

    private:
        void addFunctor(const std::string &fnName, CallerInfo *fnData);

        friend class Plugin;
        std::unordered_map<std::string, CallerInfo *> m_slots;
    };
}