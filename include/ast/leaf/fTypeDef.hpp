#pragma once

#include <vector>

#include "fLangOperand.hpp"
#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "util/fCommon.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;
	using namespace ast::symbol;

	class fTypeDef : public fLangOprnd {
		const fToken* _typeDefName;
		sp<fTypeParamClause> typeParamClause_;
		sp<fType> assignedType_;
		public:

		fTypeDef(const fToken* typeDefName) ;

		 const fToken* getTypeDefName() const;

		 void setTypeParams(sp<fTypeParamClause> typeParams) ;

		sp<fTypeParamClause> getTypeParams() const ;

		 void setAssignedType(sp<fType> &&assignedType);
		 sp<fType> getAssignedType() const ;

		void accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) override;
		std::string toString() const override;

		fLangOprndType getLangOprndType() override {
			return TYPE_DEF;
		 }
	};
}