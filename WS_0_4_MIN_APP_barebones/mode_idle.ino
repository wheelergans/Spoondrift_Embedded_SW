//********************************************************//
// Setup tasks only for idle mode
uint8_t idle_setup(){  
  drifterBoard.VDD5VOff();
  drifterBoard.VDDGPSOff();
  startIdleLedSeq();
  stopTopLight();
  return 0x00;
}

//********************************************************//
//main loop tasks only for idle mode
bool idle_tasks(){
  return false;
}





