# LLVM_Exp10_HI_LoopLabeler

LLVM_exp10_HI_LoopLabeler is used to test the frontend action HI_LoopLabeler, which will set label for loops in the source code.

HI_LoopLabeler is based on Clang LibTooling


The test can be run with the following command:

      ./LLVM_expXXXXX  <C/C++ FILE>
      

It implement a frontend action to find the declartions of arbitrary precision integer and add comments in the source code to mark those declartions.

The rewriter shoud be passed as reference but not pointer, otherwise errors will come out.

Such implementation is based on the following hierarchy:


// According the official template of Clang, this is a frontend factory with function createASTConsumer(), which
// will generator a AST consumer. We can first create a rewriter and pass the reference of the
// rewriter to the factory. Finally,  we can pass the rewriter reference to the inner visitor.
// rewriter  -> factory -> frontend-action -> ASTconsumer -> Visitor

//                         declare a rewriter
//                               |  pass the pointer to
//                  create       V
// frontend Factory ----->   FrontEnd Action
//         |                     |  create / pass the rewriter
//         |   Src Code          V
//         ------------->   AST consumer
//                               |
//                               |  generate AST
//                               V
//                            Visitor (visit the nodes in AST and do the rewritting)

IMPORTANT: Compare the differences between the following two implementation

//  virtual void HandleAnalysislationUnit(ASTContext &Context) 
//  {
//       visitor.TraverseDecl(Context.getTranslationUnitDecl());
//   }

    bool HandleTopLevelDecl(DeclGroupRef DR) override 
    { 
        for (DeclGroupRef::iterator b = DR.begin(), e = DR.end(); b != e; ++b) 
        { 
            visitor.TraverseDecl(*b); //(*b)->dump(); 
        } 
        return true; 
    } 