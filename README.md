# "Cezario Hash'as"
  Kuo skiriasi šifras ir hash'as? O gi tuo kad iš šifro galima gauti pradinį tekstą, o iš hash'o - negalima to padaryti.
  Logiškai pagalvojus - šifras taps hash'ų jeigu "rakto" gavimą ir tuo būdu ir atšifravimą padarysime neįmanomu*.  
  Šis kodas bando tai padaryti panaudojus pati žinomiausią šifrą - Cezario.

*Su meilės pagalba viskas įmanoma.


## Kaip veikia kodas
  Cezario šifras yra vienas iš paprasčiausių teksto šifravimo būdų. Tai reiškia, kad kiekviena teksto raidė pakeičiama raide, atskirta fiksuotu abėcėlės raidžių skaičiumi. Pavyzdžiui, jei apibrėžiame „2“ poslinkį, raidė „a“ bus pakeista raide „c“ (nes „a“ yra pirmoji abėcėlės raidė, o „c“ yra trečioji).

  Panašiai veikia ir mano kodas - pradinio 64 hex simbolių ilgio hash'o (FFFFFF...) simboliai yra pakeisti pagal tam tikrą poslinkį, tik tais kiekvienam simboliui nustatytas savo poslinkis o visų poslinkių seka yra sugeneruota: 
  * Simbolio char vertė yra naudojama kaip seed'as _mt1993_ generatoriui ir taip sugeneruojamas skaičius
  * Simboliams sugeneruoti skaičiai yra sumuojami
  * Gauta suma yra panaduojama kaip seed'as sugeruoti 64 poslinkių seką pagal kurią gauname hash'ą

  Tai kad ne vieną kartą yra naudojamas RNG generatorius užtikrina, kad gautas hash'as yra deterministiškas ir tai kad negalima iš jo atgauti pradinės vertės*.

  *Nesu dėl šito pilnai tikras, bet tarkim.


  ## D.U.K
  
  * "Ar nebūtų efektiviau vietoj pradinio hash'o keitimo tiesiog pagal tą seką parašyti naują hash'ą?"  
    Turbūt, bet mano siela yra labai meniška ir dar tokiu būdu galiu hash'ą pavadinti "Cezario" ir tai kietai skamba (nors pagalvojus tai šeip mažai bendro tūri su Cezario šifrų, bet čia toks **Marketingas**).
    
  * "Ar hash'as deterministiškas?"   
    Galimai.
    
  * "Ar hash'as efektyvus?"   
    Nustebčiau jeigu toks būtų.


  ## Testavimo rezultatai

  ### Deterministiškumas
  * Sugeneravus 100 000 string'ų ir iš jų gavus po 2 hash'us, nebuvo nesutapusios hash'ų poros - taigi, hash'avimo algoritmas yra deterministinis.    
    <img width="300" height="55" alt="image" src="https://github.com/user-attachments/assets/fcb4a616-a2eb-4b5b-b830-900a0b6f7686" />

  ### Lavinos efektas
  * Sugeneravus 100 000 string'ų porų kurie skiriesi tik vienų simbolių gauti tokie rezultatai:   
    <img width="300" height="1180" alt="image" src="https://github.com/user-attachments/assets/b05c9341-f00c-40d6-af08-6900c56b924e" />    
    Tai parodo lavinos efekto buvimą ir atsparumą kolizijoms.


