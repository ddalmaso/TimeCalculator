public class Use {
    public static void main(String[] args) {
		
        System.out.println("\n ------------------------------------------------------------------------------------");
        System.out.println("| Esempio di utilizzo a riga di comando delle funzionalita' di TimeCalculator in Java |");
        System.out.println(" ------------------------------------------------------------------------------------ \n");
		
        //Data e ora attuali
        DataOra dtime = new DataOra();
		Data date = new Data();
        String currentDate = date.toString();
        String currentTime = dtime.toString();
        System.out.println("Data di oggi: "+currentDate);
        System.out.println("Ore: "+currentTime);

        //Data di fine: 25 dic 2019, ore 21.30 (scelgo un orario casuale)
        DataOra fine = new DataOra(21, 30, 0, 25, 12, 2019);
		
		//Calcolo la durata temporale tra due date
		Data diffDate = new Data();
		diffDate.subDates(dtime, fine);

        DataOra diffTime = (DataOra) dtime;
        diffTime.subTimes(fine, diffTime);

        System.out.println("\nCalcolo quanto tempo manca al prossimo Natale (25 dic 2019 ore 21.30):");
        System.out.println("--> "+diffDate.Anno()+" anni, "+diffDate.Mese()+" mesi, "+diffDate.Giorno()+" giorni");
        System.out.println("--> "+diffTime.Ore()+" ore, "+diffTime.Minuti()+" minuti e "+diffTime.Secondi()+" secondi \n");

        System.out.println("Da oggi a Natale mancano in totale:");
        System.out.println("--> "+Integer.toString(diffDate.diffGiorni(dtime, fine, "g"))+" giorni,");
        System.out.println("--> "+Integer.toString(diffDate.diffGiorni(dtime, fine, "g")/7)+" settimane,");
        System.out.println("--> "+Integer.toString(diffDate.diffGiorni(dtime, fine, "l"))+" giorni lavorativi,");
        System.out.println("--> "+Integer.toString(diffDate.diffGiorni(dtime, fine, "s"))+" sabati,");
        System.out.println("--> "+Integer.toString(diffDate.diffGiorni(dtime, fine, "d"))+" domeniche,");
        System.out.println("--> "+Integer.toString(diffDate.diffGiorni(dtime, fine, "f"))+" festivi. \n");
		
        //Somme e sottrazioni tra ore minuti e secondi 
        System.out.println("Somme e sottrazioni tra ore minuti e secondi \n");

        //Considero l'ora attuale
        System.out.println(currentTime+" +");
        System.out.println("2h e 30m =");

        //Sommo 2 ore e mezza all'orario di adesso
        DataOra dueEmezza = new DataOra(2, 30, 0);
        dtime.sumTimes(dtime, dueEmezza);
        System.out.println(dtime.toString());

        System.out.println("\n"+dtime.toString()+" -");
        System.out.println("1m e 30s =");

        //Sottraggo 1 minuto e mezzo
        DataOra minEtrenta = new DataOra(0, 1, 30);
        dtime.subTimes(dtime, minEtrenta);
        System.out.println(dtime.toString());

        //Somme e sottrazioni tra data e giorni/settimane/mesi/trimestri
        System.out.println("\nSomme e sottrazioni tra data e giorni/settimane/mesi/trimestri \n ");

        System.out.println(currentDate+" +");
        System.out.println("15 giorni  =");
        date.addDays(15); System.out.println(date.toString());

        System.out.println("\n"+date.toString()+"  -");
        System.out.println("1 settimana =");
        for(int i=0; i<14; ++i) date.previous_Date(date);
        System.out.println(date.toString());

        System.out.println("\n"+date.toString()+" + ");
        System.out.println("4 mesi     =");
        date.addDays(120); System.out.println(date.toString());

        System.out.println("\n"+date.toString()+"  -");
        System.out.println("1 trimestre =");
        for(int i=0; i<90; ++i) date.previous_Date(date);
        System.out.println(date.toString());
    }
}

