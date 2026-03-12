#include "ast/leaf/fValue.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

namespace zebra::ast::leaf {

	fValue::fValue(sp<fModifiers> &&modifiers) : modifiers_(std::move(modifiers)) {
	}

	sp<fModifiers> fValue::getModifiers() const {
		return modifiers_;
	}

	void fValue::addName(sp<fAstProdSubTreeN> &&name) {
		this->names_.push_back(std::move(name));
	}

	std::vector<sp<fAstProdSubTreeN>> fValue::getNames() const {
		return names_;
	}

	void fValue::setType(sp<fType> &&type) {
		this->type_ = std::move(type);
	}

	sp<fType> fValue::getType() const {
		return type_;
	}

	void fValue::setAssignExpr(sp<fAstProdSubTreeN> &&assignExpr) {
		this->assignExpr_ = std::move(assignExpr);
	}

	sp<fAstProdSubTreeN> fValue::getAssignExpr() const {
		return assignExpr_;
	}


	void fValue::accept(std::shared_ptr<fAstNodVisitor> visitor) {
		visitor->visit(std::static_pointer_cast<fValue>(shared_from_this()));
	}

	std::string fValue::toString() const {
		return "AccessModifier()";
	}
}