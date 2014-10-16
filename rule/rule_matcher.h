#pragma once

#ifndef DIS_RULE_RULEMATCHER_H_
#define DIS_RULE_RULEMATCHER_H_

#include "../common/internal.h"
#include "rule.h"

using namespace std;


namespace dis
{
	namespace rule
	{  
		/*
			规则匹配接口类定义
			不同的RuleMatcher实现类，依据每一个operation中定义的regex，执行匹配验证，获取对应的operation对象
		*/
		class RuleMatcher
		{
			public:
				static RuleMatcher *Instance()
				{
					static RuleMatcher rule_matcher;
					return &rule_matcher;
				}
			
			/*
				根据传入的条件，匹配regex正则
			*/
			Operation*  getOperation(string url);
			
		};
     }	
}
#endif 

