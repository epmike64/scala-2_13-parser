#include "ast/leaf/fStableId.hpp"

#include <string>

namespace zebra::ast::leaf {

	fTPair::fTPair(const fToken *id, const fTKnd *const kind)
			: id_(id), kind_(kind) {
		assert(id_ != nullptr);
	}

	fTKnd *fTPair::getKnd() const {
		return const_cast<fTKnd *>(kind_);
	}

	const fToken* fTPair::getId() const {
		return id_;
	}

	std::string fTPair::toString() const {
		return id_->toString() + ":" + kind_->toString();
	}

	fStableId::fStableId(bool isPath) : isPath_(isPath) {}

	void fStableId::addTId(const fToken *tId) {
		tpairs_.push_back(ms<fTPair>(tId, fTKnd::T_ID));
	}

	std::vector<sp<fTPair>>&  fStableId::getTPairs() {
		return tpairs_;
	}

	bool  fStableId::isPath() const {
		return isPath_;
	}

	void  fStableId::setIsKwType(bool isKwType) {
		isKwType_ = isKwType;
	}

	bool  fStableId::isKwType() const {
		return isKwType_;
	}

	void fStableId::addSuper(const fToken* s) {
		assert(s->getTKind() == fTKnd::T_SUPER);
		tpairs_.push_back(ms<fTPair>(s, fTKnd::T_SUPER));
	}

	void fStableId::addThis(const fToken* t) {
		assert(t->getTKind() == fTKnd::T_THIS);
		tpairs_.push_back(ms<fTPair>(t, fTKnd::T_THIS));
	}

	void fStableId::addClassQualifier(const fToken* tId) {
		tpairs_.push_back(ms<fTPair>(tId, fTKnd::T_CLASS_QUALIFIER));
	}

	fTKnd *fStableId::getLastTKind() {
	  if (tpairs_.empty()) {
	    return nullptr;
	  }
	  return tpairs_.operator[](tpairs_.size() - 1)->getKnd();
	}


	void  fStableId::accept(std::shared_ptr<fAstNodVisitor> visitor, ssc s)  {
		visitor->visit(std::static_pointer_cast<fStableId>(shared_from_this()), s);
	}


	void fStableId::setSingletonType(const bool isSingletonType) {
		isSingletonType_ = isSingletonType;
	}

	bool fStableId::isSingletonType() const {
		return isSingletonType_;
	}

	std::string fStableId::getQualName() {
		std::string qualName;
		for (int i = 0; i < tpairs_.size(); i++) {
			qualName += tpairs_[i]->getId()->getTStrVal();
			if (i < tpairs_.size() - 1) {
				qualName += ".";
			}
		}
		return qualName;
	}

	std::string fStableId::toString() const {

		std::stringstream ss;
		ss << "StableId(";
		for (std::size_t i = 0; i < tpairs_.size(); i++) {
			ss << tpairs_[i]->getId()->toString();
			if (i < tpairs_.size() - 1) {
				ss << ".";
			}
		}
		ss << ")";
		return ss.str();
	}

}
