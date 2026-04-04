#include "ast/leaf/fAnnotation.hpp"

namespace zebra::ast::leaf {

	fAnnotation::fAnnotation(sp<fParamType> simpleType) : simpleType_(std::move(simpleType)) {}

	sp<fParamType> fAnnotation::getSimpleType() const {
		return simpleType_;
	}

	void fAnnotation::addArgExprs(sp<fAstProdSubTreeN> &&arg) {
		if (!argsExprs_) {
			argsExprs_ = ms<std::vector<sp<fAstProdSubTreeN>>>();
		}
		argsExprs_->push_back(std::move(arg));
	}

	void fAnnotation::accept(std::shared_ptr<fAstNodVisitor> visitor, sbx s)  {
		visitor->visit(std::static_pointer_cast<fAnnotation>(shared_from_this()), s);
	}


	std::string fAnnotation::toString() const  {
		return "Annotation(simpleType=" + (simpleType_ ? simpleType_->toString() : "null") +
		       ", argsExprs=[" + [&]() {
			std::string result;
			if (argsExprs_) {
				for (const auto& arg : *argsExprs_) {
					result += (arg ? arg->toString() : "null") + ", ";
				}
			}
			return result;
		}() + "])";
	}

}