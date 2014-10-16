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
			����ƥ��ӿ��ඨ��
			��ͬ��RuleMatcherʵ���࣬����ÿһ��operation�ж����regex��ִ��ƥ����֤����ȡ��Ӧ��operation����
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
				���ݴ����������ƥ��regex����
			*/
			Operation*  getOperation(string url);
			
		};
     }	
}
#endif 

