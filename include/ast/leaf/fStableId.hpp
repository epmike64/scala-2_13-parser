#pragma once
#include <vector>

#include "../fLangOperand.hpp"
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
		const fToken *getId() const ;
		std::string toString() const ;
	};

	//
	class fStableId : public fLangOprnd {
		const bool isPath_;
		bool isKwType_ = false;
		std::vector<sp<fTPair>> tpairs_;
		bool isSingletonType_ = false;  // SimpleType '.' 'type'
		public:

		explicit fStableId(bool isPath) ;

		void addTId(const fToken *tId) ;

		 std::vector<sp<fTPair>>& getTPairs() ;

		void setSingletonType(const bool isSingletonType) ;
		bool isSingletonType() const ;

		 bool isPath() const;

		 void setIsKwType(bool isKwType) ;

		 bool isKwType() const ;

		void addSuper(const fToken *s);

		void addThis(const fToken* t) ;

		void addClassQualifier(const fToken *tId);

		fTKnd *getLastTKind();

		std::string getQualName();

		void accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) override;

		std::string toString() const override;

		fLangOprndType getLangOprndType() override {
			return STABLE_ID;
		 }

	};
}
