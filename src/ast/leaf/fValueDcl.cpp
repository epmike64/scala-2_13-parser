#include "ast/leaf/fValueDcl.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

#include "ast/leaf/fModifiers.hpp"
#include "ast/leaf/fType.hpp"

namespace zebra::ast::leaf {

	fValueDcl::fValueDcl(sp<fModifiers> &&modifiers, lex::kind::fVarMutTypeE mutabilityType) : modifiers_(std::move(modifiers)), mutabilityType_(mutabilityType) {}

	sp<fModifiers> fValueDcl::getModifiers() const {
		return modifiers_;
	}

	void fValueDcl::addName(sp<fAstProdSubTreeN> &&name) {
		this->names_.push_back(std::move(name));
	}

	std::vector<sp<fAstProdSubTreeN>> fValueDcl::getNames() const {
		return names_;
	}

	void fValueDcl::setType(sp<fType> &&type) {
		this->type_ = std::move(type);
	}

	sp<fType> fValueDcl::getType() const {
		return type_;
	}

	void fValueDcl::setAssignExpr(sp<fAstProdSubTreeN> &&assignExpr) {
		this->assignExpr_ = std::move(assignExpr);
	}

	sp<fAstProdSubTreeN> fValueDcl::getAssignExpr() const {
		return assignExpr_;
	}


	void fValueDcl::accept(std::shared_ptr<fAstNodVisitor> visitor, sbx s) {
		visitor->visit(std::static_pointer_cast<fValueDcl>(shared_from_this()), s);
	}

	std::string fValueDcl::toString() const {
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
