#include "loadcommand_symtab.h"
#include "machheader.h"


MOEX_NAMESPACE_BEGIN

void LoadCommand_LC_SYMTAB::LazyInit(){
    if(inited_)return;
    inited_ = true;

    // symbol list
    char * symbol_offset = (char*)GetSymbolTableOffset();
    if(header_->is64()){
        for(uint32_t idx = 0; idx < GetSymbolTableSize(); ++idx){
            struct nlist_64 * cur = reinterpret_cast<struct nlist_64*>(symbol_offset + idx * sizeof(struct nlist_64));
            NListPtr symbol = std::make_shared<NList>();
            symbol->Init(cur,ctx_,true);
            nlists_.push_back(symbol);
        }
    }else{
        for(uint32_t idx = 0; idx < GetSymbolTableSize(); ++idx) {
            struct nlist *cur = reinterpret_cast<struct nlist *>(symbol_offset + idx * sizeof(struct nlist));
            NListPtr symbol = std::make_shared<NList>();
            symbol->Init(cur, ctx_,false);
            nlists_.push_back(symbol);
        }
    }

    // string table
    char * stringtable_offset = (char*)GetStringTableOffset();
    for(uint32_t idx = 0; idx < GetStringTableSize(); ++idx) {

    }
}

MOEX_NAMESPACE_END