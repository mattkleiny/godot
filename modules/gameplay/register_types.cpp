#include "register_types.h"

#include "gameplay.h"

void initialize_gdscript_module(ModuleInitializationLevel p_level) {
	if (p_level == MODULE_INITIALIZATION_LEVEL_SERVERS) {
		ClassDB::register_class<GameMode>();
		ClassDB::register_class<Pawn>();
		ClassDB::register_class<PawnController>();
	}
}

void uninitialize_gdscript_module(ModuleInitializationLevel p_level) {
	if (p_level == MODULE_INITIALIZATION_LEVEL_SERVERS) {
	}
}
