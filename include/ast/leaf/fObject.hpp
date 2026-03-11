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

	class fObject : public fAstOprndNod {
		const bool isCaseClass_;
		const fToken* objectName_;
		const sp<fModifiers> modifiers_;
		sp<fTemplate> extendsTemplate_;

	public:

		fObject(const fToken* objectName, sp<fModifiers> &&modifiers, bool isCaseClass) ;

		 bool isCaseClass() const ;

		 sp<fModifiers> getModifiers() const ;

		 void setExtendsTemplate(sp<fTemplate> &&extendsTemplate) ;

		 sp<fTemplate> getExtendsTemplate() const ;
		const fToken* getObjectName() const ;

		void accept(std::shared_ptr<fAstNodVisitor> visitor) override;

		std::string toString() const override;
	};
}
