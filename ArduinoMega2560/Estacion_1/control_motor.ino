int direc=0;

int motor_Girar_Derecha()
{
  digitalWrite(Ena, LOW);
  digitalWrite(Dir, LOW);
  direc = 1;
  return direc;
}

int motor_Girar_Izquierda()
{
  digitalWrite(Ena, LOW);
  digitalWrite(Dir, HIGH);
  direc = 1;
  return direc;
}

int motor_Parar()
{
  digitalWrite(Ena, HIGH);
  direc = 0;
  return direc;
}
