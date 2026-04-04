
#include "ast/leaf/fAnnotations.hpp"

namespace zebra::ast::leaf {

	void fAnnotations::accept(std::shared_ptr<fAstNodVisitor> visitor, sbx s) {
		visitor->visit(std::static_pointer_cast<fAnnotations>(shared_from_this()), s);
	}

	void fAnnotations::addAnnotation(sp<fAnnotation> annotation) {
		if (!annotations_) {
			annotations_ = ms<std::vector<sp<fAnnotation>>>();
		}
		annotations_->push_back(std::move(annotation));
	}

	PVecP<fAnnotation> fAnnotations::annotations() {
		return annotations_;
	}

	std::string fAnnotations::toString() const {
		std::ostringstream oss;
		if (annotations_) {
			oss << "annotations: [";
			for (const auto& annotation : *annotations_) {
				oss << annotation->toString() << ", ";
			}
			oss << "]";
		} else {
			oss << "no annotations";
		}
		return oss.str();
	}
}
