#pragma once
#include <vector>

#include "fModifiers.hpp"
#include "util/fCommon.hpp"
#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstProdSubTreeN.hpp"
#include "lex/token/fToken.hpp"

namespace zebra::ast::leaf {
	using namespace zebra::ast::node;
	using namespace zebra::util;

	class fObjectDef : public fAstOprndNod {
		const bool isCaseObj_;
		const fToken* identName_;
		const sp<fModifiers> modifiers_;
		sp<fTemplate> extendsTemplate_;

	public:

		fObjectDef(const fToken* objectName, sp<fModifiers> &&modifiers, bool isCaseClass) ;

		 bool isCaseObj() const ;

		 sp<fModifiers> getModifiers() const ;

		 void setExtendsTemplate(sp<fTemplate> &&extendsTemplate) ;

		 sp<fTemplate> getExtendsTemplate() const ;
		const fToken* getIdentToken() const ;
		const std::string& getIdentName() const ;

		void accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) override;

		std::string toString() const override;
	};
}
