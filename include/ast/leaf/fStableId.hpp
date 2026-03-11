#pragma once
#include <vector>

#include "lex/kind/fLangOperatorKind.hpp"
#include "ast/node/fAstNodVisitor.hpp"

namespace zebra::ast::leaf {
	using namespace zebra::ast::node;
	using namespace zebra::lex::kind;

	//
	class fTPair {
		const fToken *id_;
		const fTKnd *const kind_;
	public:
		fTPair(const fToken *id, const fTKnd *const kind);
		fTKnd *getKnd() const ;
		std::string toString() const ;
	};

	//
	class fStableId : public fAstOprndNod {
		const bool isPath_;
		bool isKwType_ = false;
		std::vector<sp<fTPair>> tpairs_;
		public:

		explicit fStableId(bool isPath) ;

		void addTId(const fToken *tId) ;

		 std::vector<sp<fTPair>>& getTPairs() ;

		 bool isPath() const;

		 void setIsKwType(bool isKwType) ;

		 bool isKwType() const ;

		void addSuper(const fToken *s);

		void addThis(const fToken* t) ;

		void addClassQualifier(const fToken *tId);

		fTKnd *getLastTKind();

		void accept(std::shared_ptr<fAstNodVisitor> visitor) override;

		std::string toString() const override;

	};
}
