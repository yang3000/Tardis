#pragma once

#include "Base.h"
#include "Caller.h"
#include "FreeCaller.h"
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
		ParamInfo(const std::string& name = "", const std::string& desc = "", const std::string& type = "") : 
		m_name(name),
		m_type(type),
		m_desc(desc)
		{}

		std::string m_name;
		std::string m_type;
		std::string m_desc;
	};

	struct CallerInfo
	{
		CallerInfo(const char *pName, ICaller *p_caller) : 
		name(pName), 
		caller(p_caller) 
		{}

		~CallerInfo() { delete caller; }

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
	template<typename...Args>
	struct Parameterized {
		typename GenSeq<sizeof...(Args)>::Type m_seq;

		size_t ParamLen = sizeof...(Args);

		Parameterized(std::vector<ParamInfo>& desData, std::vector<ParamInfo>& srcData) :
			m_desData(desData),
			m_srcData(srcData)
		{
			assert(ParamLen <= srcData.size());
		}

		template<typename T, int I>
		bool setParam()
		{
			m_desData[I].m_name = m_srcData[I].m_name;
			m_desData[I].m_desc = m_srcData[I].m_desc;
			m_desData[I].m_type = ValueHelper<T>::getDataTypeName();
			return true;
		}

		template<int I>
		bool addParam() { m_desData.emplace_back(); return true; }

		// template<typename... T> void nothing(T...) {}
		// template<int ...I> void setParamLen(Seq<I...>) { nothing(addParam<I>()...); }
        // template<int ...I> void initParams(Seq<I...>) { nothing(setParam<Args, I>()...); }

        template<int ...I>
		void setParamLen(Seq<I...>) { (addParam<I>(), ...); }

		template<int ...I>
		void initParams(Seq<I...>) { (setParam<Args, I>(), ...); }

		void operator()()
		{
			setParamLen(m_seq);
			initParams(m_seq);
		}

		std::vector<ParamInfo>& m_desData;
		std::vector<ParamInfo>& m_srcData;
	};

	class CallerContainer final
	{
	public:
		CallerContainer() = default;
		~CallerContainer();

		template<typename T, typename R, typename...Args>
		void registerFunctor(const char* fnName, R(T::* fn)(Args...), T* pObj, std::vector<ParamInfo> paramData)
		{
			CallerInfo* t_fndata = new CallerInfo(fnName, new Caller<T, R, Args...>(fn, pObj));
			Parameterized<Args...>(t_fndata->params, paramData)();

			addFunctor(fnName, t_fndata);
		}

		template<typename R, typename...Args>
		void registerFunctor(const char* fnName, R(*fn)(Args...), std::vector<ParamInfo> paramData)
		{
			CallerInfo* t_fndata = new CallerInfo(fnName, new FreeCaller<R, Args...>(fn));
			Parameterized<Args...>(t_fndata->params, paramData)();

			addFunctor(fnName, t_fndata);
		}

		CallerInfo* get(const std::string& name);

	private:
		void addFunctor(const std::string& fnName, CallerInfo* fnData);

        friend class Plugin;
		std::unordered_map<std::string, CallerInfo*> m_slots;
	};
}