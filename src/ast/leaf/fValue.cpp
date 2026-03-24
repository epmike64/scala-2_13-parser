#include "ast/leaf/fValue.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

#include "ast/leaf/fModifiers.hpp"
#include "ast/leaf/fType.hpp"

namespace zebra::ast::leaf {

	fValue::fValue(sp<fModifiers> &&modifiers, lex::kind::fVarMutTypeE mutabilityType) : modifiers_(std::move(modifiers)), mutabilityType_(mutabilityType) {}

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


	void fValue::accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) {
		visitor->visit(std::static_pointer_cast<fValue>(shared_from_this()), s);
	}

	std::string fValue::toString() const {
		std::ostringstream oss;
		if (modifiers_) {
			oss << "modifiers: " << modifiers_->toString() << ", ";
		}
		oss << "var|val name is given as vector<AstProdSubTreeN>";
		if (type_) {
			oss << ", type: " << type_->toString();
		}
		if (assignExpr_) {
			oss << ", assignExpr: " << assignExpr_->toString();
		}
		return oss.str();
	}
}
