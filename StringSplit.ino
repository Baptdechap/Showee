#define SPLITTERS 16 // nombre de dÃ©limiteurs MAX pris en compte

String Subs[SPLITTERS];
int SplitIndex[SPLITTERS];

void String_Split(char Splitter, String _string)
{
  int i;
  int Index=0;
  int Nsubs;
          for(i=0; i<SPLITTERS; i++)
          {
            SplitIndex[i]=_string.indexOf(Splitter,Index);
            Index=SplitIndex[i]+1;
            if(!Index) break;
          }
          Nsubs=i+1;
          Index=-1;
          for(i=0; i<Nsubs; i++)
          {
            Subs[i]=  _string.substring(Index+1,SplitIndex[i]);
            Serial.print("Sub ");
            Serial.print(i);
            Serial.print(": ");
            Serial.println(Subs[i]);
            Index=SplitIndex[i];
          }
          
          for(i=0; i<SPLITTERS; i++)
          {
            SplitIndex[i]=-1;
          }
}

