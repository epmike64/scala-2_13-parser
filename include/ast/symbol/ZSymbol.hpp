#pragma once

#include "ZLangConstruct.hpp"
#include "ast/leaf/fVariantTypeParam.hpp"
#include "ast/leaf/fType.hpp"
#include <functional>

#include "ZSymbol.hpp"

namespace zebra::ast::symbol {
	class ZProdSubTreeN;

	using namespace zebra::ast::node;
	using namespace zebra::ast::leaf;
	using namespace zebra::lex::kind;
	using namespace zebra::util;

	class ZId {
	protected:
		std::string qualId_;
	public:
		ZId(std::string qId) : qualId_(std::move(qId)) {}
		ZId(const ZId&) = default;
		ZId(ZId&&) = default;
		ZId& operator=(const ZId&) = default;
		ZId& operator=(ZId&&) = default;

		const std::string& qualId() const { return qualId_; }

		bool operator==(const ZId& other) const {
			return qualId_ == other.qualId_;
		}
	};

	class ZSymbol {
	protected:
		const ZId zId_;
	public:
		ZSymbol(ZId zId) : zId_(std::move(zId)) {}
		virtual ~ZSymbol() = default;
		virtual  ZLangConstruct getZLangConstruct() = 0;
		const ZId zId() const { return zId_; }
	};

	class ZUnit : public ZSymbol {
	protected:
		PVecP<ZUnit> subUnits_;
		PVec<std::string> imports_;
		std::string declName_;
		const ZLangConstruct langConstruct_;
		sp<ZProdSubTreeN> zcpt_;
	public:
		explicit ZUnit(ZId zId, ZLangConstruct c) : ZSymbol(std::move(zId)),  langConstruct_(c) {}
		~ZUnit() override = default;

		void addSubUnit(sp<ZUnit> subUnit)  {
			subUnits_->emplace_back(std::move(subUnit));
		}
		void addImport(std::string import_) {
			imports_->emplace_back(std::move(import_));
		}
		void addImports(sp<std::vector<std::string>> imports) {
			for (auto it = imports_->begin(); it != imports_->end(); ++it) {
				imports_->emplace_back(std::move(*it));
			}
		}

		void setDeclName(std::string n) {
			declName_ =std::move(n);
		}

		const std::string& getDeclName() {
			return declName_;
		}

		ZLangConstruct getZLangConstruct() override {
			return langConstruct_;
		}

		bool containsImports(const std::string& s) {
			for (auto it = imports_->begin(); it != imports_->end(); ++it) {
				if (*it == s) {
					return true;
				}
			}
			return false;
		}
		 void setProdSubTreeN(sp<ZProdSubTreeN> zcpt) {
			this->zcpt_ = std::move(zcpt);
		}
	};


	class ZTrait: public ZUnit {
	public:
		ZTrait(ZId zId) : ZUnit(std::move(zId), ZLangConstruct::Z_TRAIT) {}
		// ...existing code...
	};

	class ZDecl: public ZUnit {
	public:
		ZDecl(ZId zId) : ZUnit(std::move(zId), Z_DECL) {}
		// ...existing code...
	};

	class ZFunc: public ZUnit {
	public:
		ZFunc(ZId zId) : ZUnit(std::move(zId), Z_FUNC) {}
	};

	// class ZClassParam: public ZUnit {
	// protected:
	// 	const bool isMutable_;
	// 	public:
	// 	ZClassParam(ZId zId, bool isMutable) : ZUnit(std::move(zId), Z_CLASS_PARAM), isMutable_(isMutable) {}
	// };

	class ZProdSubTreeN: public ZUnit {
	protected:
		PVecP<fAstNod> polishCalcStack; //RPN - reverse polish notation
		public:
		ZProdSubTreeN(ZId zId) : ZUnit(std::move(zId), Z_PROD_SUB_TREE_NOD) {}
		ZProdSubTreeN(ZId zId, ZLangConstruct c) : ZUnit(std::move(zId), c) {}

		void setPolishSS(sp<std::vector<sp<fAstNod> > > &&astRPN) {
			this->polishCalcStack = std::move(astRPN);
		}

		sp<std::vector<sp<fAstNod> > > getPolishSS() const {
			return polishCalcStack;
		}
	};

	class ZType : public ZProdSubTreeN {
	public:
		ZType(ZId zId) : ZProdSubTreeN(std::move(zId), Z_TYPE) {}
		ZType(ZId zId, ZLangConstruct c) : ZProdSubTreeN(std::move(zId), c) {}

	};

	class ZParamType: public ZType {
		public:
		ZParamType(ZId zId) : ZType(std::move(zId), Z_PARAM_TYPE) {}
		ZParamType(ZId zId, ZLangConstruct c) : ZType(std::move(zId), c) {}
	};


	class ZClassParam: public ZParamType {
	protected:
		const bool isMutable_;
	public:
		ZClassParam(ZId zId, bool isMutable) : ZParamType(std::move(zId), Z_CLASS_PARAM), isMutable_(isMutable) {}
	};

	class ZClassConstr: public ZUnit {
	protected:
		PVecP<ZClassParam> clsParams_;
	public:
		ZClassConstr(ZId zId) : ZUnit(std::move(zId), Z_CLASS_CONSTR) {}
	};

	class ZClass : public ZTrait {
		sp<ZClass> parentClass_;
		PVecP<ZTrait> traits_;
		PVecP<ZTypeParam> typeParams_;
		PVecP<ZClassConstr> constrs_;
		PVecP<ZDecl> decls_;
		PVecP<ZFunc> funcs_;
	public:
		ZClass(ZId zId) : ZTrait(std::move(zId)) {}

	};

	class ZProgram: public ZUnit {
		public:
		ZProgram(ZId zId) : ZUnit(std::move(zId), Z_PROGRAM) {}
	};

	class ZCompileUnit: public ZUnit {
	public:
		ZCompileUnit(ZId zId) : ZUnit(std::move(zId), Z_COMPILATION_UNIT) {
			declName_ = "_ROOT_PKG_";
		}
		void setPackage(std::string n) {
			declName_ += "." + n;
		}

		void addClass(sp<ZClass> cls) {
			addSubUnit(cls);
		}
	};


}

namespace std {
	template <>
	struct hash<zebra::ast::symbol::ZId> {
		std::size_t operator()(const zebra::ast::symbol::ZId& id) const noexcept {
			return std::hash<std::string>{}(id.qualId());
		}
	};
}
