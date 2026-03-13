#pragma once
#include <memory>
#include "ast/node/fAstNodKndE.hpp"

namespace zebra::ast::node {

	// Forward declaration — fAstNodVisitor.hpp includes leaf headers which
	// inherit from fAstNod, so including it here would create a circular dependency.
	class fAstNodVisitor;

	class fAstNod : public std::enable_shared_from_this<fAstNod>{
	 protected:
	 	std::shared_ptr<fAstNod> astLeftN_;
	 	std::shared_ptr<fAstNod> astRightN_;
	 	std::shared_ptr<fAstNod> astParentN_;

	 public:

		virtual ~fAstNod() = default;

	 	std::shared_ptr<fAstNod> getAstLeftN() const {return astLeftN_;}
	 	std::shared_ptr<fAstNod> getAstRightN() const {return astRightN_;}
	 	std::shared_ptr<fAstNod> getAstParentN() const {return astParentN_;}

	 	virtual void setAstLeftN(std::shared_ptr<fAstNod> astLeftN) = 0;
	 	virtual void setAstRightN(std::shared_ptr<fAstNod> astRightN) = 0;

	 	virtual bool isOperator()  = 0;
	 	virtual fAstNodKndE astNKndE()  = 0;
		virtual void accept(std::shared_ptr<fAstNodVisitor> visitor) = 0;
		virtual void setAstParentN(std::shared_ptr<fAstNod> p);

		virtual std::string toString() const = 0;
	};

}
