cmake_minimum_required(VERSION 4.1)
project(zebra-4-backend)

set(CMAKE_CXX_STANDARD 20)

include_directories(
		${CMAKE_SOURCE_DIR}/include
)



add_executable(zebra-4-backend

		src/zebra_main.cpp

		include/ast/node/fAstNod.hpp
		include/ast/node/fAstNodKndE.hpp
		include/ast/node/fAstOprndNod.hpp
		include/ast/node/fAstOptrNod.hpp
		include/ast/node/fAstProdSubTreeN.hpp
		include/ast/node/fAstRootOptrNod.hpp

		include/lex/util/fUtil.hpp
		include/lex/util/fTBuffer.hpp
		include/lex/util/fLangMethNameCheck.hpp
		include/lex/kind/fLangModifierTypeE.hpp

		include/lex/kind/fLangOperatorKind.hpp
		include/lex/token/fNumToken.hpp
		include/lex/fLexerIFace.hpp
		include/lex/fLexerImpl.hpp

		include/util/fCommon.hpp

		include/parse/fParser.hpp
		include/parse/fParseHelp.hpp
		include/parse/fLangGrmrProdE.hpp

		include/ast/leaf/fCompileUnit.hpp
		include/ast/leaf/fLiteral.hpp
		include/ast/leaf/fStableId.hpp

		include/ast/node/fAstNodVisitor.hpp
		include/ast/tree/fLangAstVisitor.hpp


		include/ast/leaf/fObject.hpp
		include/ast/leaf/fClassDef.hpp
		include/ast/leaf/fValueDef.hpp
		include/ast/leaf/fType.hpp
		include/ast/leaf/fIf.hpp
		include/ast/leaf/fWhile.hpp
		include/ast/leaf/fFunSig.hpp
		include/ast/leaf/fFun.hpp
		include/ast/leaf/fClassConstr.hpp
		include/ast/leaf/fBlock.hpp
		include/ast/leaf/fClassParam.hpp
		include/ast/leaf/fImport.hpp
		include/ast/leaf/fModifier.hpp
		include/ast/leaf/fTypeArgs.hpp
		include/ast/leaf/fPackage.hpp
		include/ast/leaf/fAccessModifier.hpp
		include/ast/leaf/fParamType.hpp
		include/ast/leaf/fAccessQualifier.hpp
		include/ast/leaf/fCaseClause.hpp
		include/ast/leaf/fClassParamClauses.hpp
		include/ast/leaf/fCaseClauses.hpp


		src/parse/fParseHelp.cpp
		src/parse/fParser.cpp
		src/parse/fAst.cpp

		src/ast/node/fAstOprndNod.cpp
		src/ast/node/fAstOptrNod.cpp
		src/ast/node/fAstProdSubTreeN.cpp
		src/ast/node/fAstNod.cpp
		src/ast/tree/fLangAstVisitor.cpp

		src/lex/kind/fLangOperatorKind.cpp
		src/lex/kind/fTKnd.cpp

		src/lex/token/fToken.cpp
		src/lex/token/fNumToken.cpp
		src/lex/fReader.cpp
		src/lex/fTokzr.cpp
		src/lex/util/fUtil.cpp
		src/lex/util/fLangMethNameCheck.cpp

		src/ast/leaf/fClassDef.cpp
		src/ast/leaf/fObject.cpp
		src/ast/leaf/fLiteral.cpp
		src/ast/leaf/fCompileUnit.cpp
		src/ast/leaf/fStableId.cpp
		src/ast/leaf/fValueDef.cpp
		src/ast/leaf/fType.cpp
		src/ast/leaf/fIf.cpp
		src/ast/leaf/fWhile.cpp
		src/ast/leaf/fAccessModifier.cpp
		src/ast/leaf/fBlock.cpp
		src/ast/leaf/fClassConstr.cpp
		src/ast/leaf/fClassParam.cpp
		src/ast/leaf/fFun.cpp
		src/ast/leaf/fFunSig.cpp
		src/ast/leaf/fImport.cpp
		src/ast/leaf/fModifier.cpp
		src/ast/leaf/fPackage.cpp
		src/ast/leaf/fParamType.cpp
		src/ast/leaf/fTypeArgs.cpp
		include/ast/leaf/fClassParents.hpp
		include/ast/leaf/fClassTemplate.hpp
		include/ast/leaf/fConstrBlock.hpp
		include/ast/leaf/fFor.hpp
		include/ast/leaf/fGenerator.hpp
		include/ast/leaf/fLocalModifier.hpp
		include/ast/leaf/fNamedFun.hpp
		include/ast/leaf/fOverrideModifier.hpp
		include/ast/leaf/fParam.hpp
		include/ast/leaf/fParamClauses.hpp
		include/ast/leaf/fParamTypes.hpp
		include/ast/leaf/fReturn.hpp
		include/ast/leaf/fTemplate.hpp
		include/ast/leaf/fTemplateBody.hpp
		include/ast/leaf/fThisFun.hpp
		include/ast/leaf/fThrow.hpp
		include/ast/leaf/fTraitDef.hpp
		include/ast/leaf/fTry.hpp
		include/ast/leaf/fTypeDef.hpp
		include/ast/leaf/fTypeParam.hpp
		include/ast/leaf/fUnderscore.hpp
		include/ast/leaf/fValue.hpp
		include/ast/leaf/fValueDecl.hpp
		include/ast/leaf/fVariantTypeParam.hpp
		include/ast/leaf/fId.hpp
		include/ast/leaf/fIds.hpp

		src/ast/leaf/fAccessQualifier.cpp
		src/ast/leaf/fCaseClause.cpp
		src/ast/leaf/fCaseClauses.cpp
		src/ast/leaf/fClassParamClauses.cpp
		src/ast/leaf/fClassParents.cpp
		src/ast/leaf/fClassTemplate.cpp
		src/ast/leaf/fConstrBlock.cpp
		src/ast/leaf/fFor.cpp
		src/ast/leaf/fGenerator.cpp
		src/ast/leaf/fId.cpp
		src/ast/leaf/fIds.cpp
		src/ast/leaf/fLocalModifier.cpp
		src/ast/leaf/fNamedFun.cpp
		src/ast/leaf/fOverrideModifier.cpp
		src/ast/leaf/fParamClauses.cpp
		src/ast/leaf/fParamTypes.cpp
		src/ast/leaf/fReturn.cpp
		src/ast/leaf/fTemplate.cpp
		src/ast/leaf/fTemplateBody.cpp
		src/ast/leaf/fThisFun.cpp
		src/ast/leaf/fThrow.cpp
		src/ast/leaf/fTraitDef.cpp
		src/ast/leaf/fTry.cpp
		src/ast/leaf/fTypeDef.cpp
		src/ast/leaf/fTypeParam.cpp
		src/ast/leaf/fUnderscore.cpp
		src/ast/leaf/fValue.cpp
		src/ast/leaf/fValueDecl.cpp
		src/ast/leaf/fVariantTypeParam.cpp
		include/lex/kind/fAccessQualifierE.hpp
		include/ast/leaf/fModifiers.hpp
		include/lex/kind/fVariableMutabilityTypeE.hpp
		include/lex/kind/fVarianceE.hpp
		src/ast/leaf/fModifiers.cpp
		src/ast/leaf/fParam.cpp
		include/lex/kind/fLangPseudoOperatorKindE.hpp
		src/lex/kind/fLangPseudoOperatorKindE.cpp
		src/ast/tree/fLangAstVisitor.cpp


)

target_compile_definitions(zebra-4-backend PRIVATE
		PROJECT_ROOT="${CMAKE_SOURCE_DIR}"
)
