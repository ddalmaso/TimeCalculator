import java.lang.*;
import java.util.Calendar;
import java.text.SimpleDateFormat;

public class Data {
    private int anno;   // 1753 - 9999
    private int mese;   // 1 - 12
    private int giorno; // 1 - 31

    public static final int Anno_Min = 1900;
    public static final int[] Giorni_Del_Mese = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	public static final String[] Settimana = {"Domenica", "Lunedi", "Martedi", "Mercoledi",
                                             "Giovedi", "Venerdi", "Sabato"};

    public static boolean Bisestile(int a) {
        return ((a % 4 == 0 && a % 100 != 0) || (a % 400 == 0));
    }

    public static boolean DataValida(int g, int m, int a) {
        if (a < Anno_Min) return false;
        if ((m < 1) || (m > 12)) return false;
        if ((g < 1) || (g > 31)) return false;
        switch (m) {
            case 1: return true;
            case 2: return (Bisestile(a) ? g <= 29 : g <= 28);
            case 3: return true;
            case 4: return g < 31;
            case 5: return true;
            case 6: return g < 31;
            case 7: return true;
            case 8: return true;
            case 9: return g < 31;
            case 10: return true;
            case 11: return g < 31;
            default: return true;
        }
    }

    public Data(int g, int m, int a) throws IllegalArgumentException {
        if (!DataValida(g, m, a))
            throw new IllegalArgumentException();
        anno = a;
        mese = m;
        giorno = g;
    }

    //imposta la data di default ad oggi
    public Data() {
        String year = new SimpleDateFormat("yyyy").format(new java.util.Date());
        anno = Integer.parseInt(year);
        String month = new SimpleDateFormat("MM").format(new java.util.Date());
        mese = Integer.parseInt(month);
        String day = new SimpleDateFormat("dd").format(new java.util.Date());
        giorno = Integer.parseInt(day);
    }

    public int Giorno() { return giorno; }
    public int Mese() { return mese; }
    public int Anno() { return anno; }

    public void setGiorno(int g) { giorno = g; }
    public void setMese(int m) { mese = m; }
    public void setAnno(int a) { anno = a; }
    public void setData(int g, int m, int a) {
        setGiorno(g);
        setMese(m);
        setAnno(a);
    }


    public boolean Festivo() {
            if(((giorno == 1) && (mese == 1)) || //Capodanno
                ((giorno == 6) && (mese == 1)) || //Epifania
                ((giorno == 25) && (mese == 4)) ||    //festa della Liberazione
                ((giorno == 1) && (mese == 5)) || //festa dei lavoratori
                ((giorno == 2) && (mese == 6)) || //festa della Repubblica
                ((giorno == 15) && (mese == 8)) ||    //Ferragosto
                ((giorno == 1) && (mese == 11)) ||    //giorni di Tutti i Santi
                ((giorno == 8) && (mese == 12)) ||   //festa dell'Immacolata Concezione
                ((giorno == 25) && (mese == 12)) ||   //giorno di Natale
                ((giorno == 26) && (mese == 12))) {  //giorno di Santo Stefano
                                return true;
                        }
        return false;
    }

    public String toString() {
        StringBuilder s = new StringBuilder();
        if (giorno < 10) s.append("0");
        s.append(String.valueOf(giorno));
        s.append("/");
        if (mese < 10) s.append("0");
        s.append(String.valueOf(mese));
        s.append("/");
        s.append(String.valueOf(anno));
        return s.toString();
    }

    public boolean isEqual(Data d) {
        if (!DataValida(anno, mese, giorno)) { return false; };
        if (!DataValida(d.Anno(), d.Mese(), d.Giorno())) { return false; };
        return ((anno == d.Anno()) && (mese == d.Mese()) && (giorno == d.Giorno()));
    }

    public boolean isNotEqual(Data d) {
        //return !(this.isEqual(d));
                return ((anno != d.Anno()) || (mese != d.Mese()) || (giorno != d.Giorno()));
    }

    public boolean isLesser(Data d) {
        if(anno < d.Anno()) return true;
        if(anno == d.Anno())
        {
            if(mese < d.Mese()) return true;
            if(mese == d.Mese()){
                if(giorno < d.Giorno()) return true;
            }
        }
        return false;
    }

    //aggiunge un fissato numero di giorni alla data chiamante
    public void addDays(int daysToAdd) {
        do
        {
            //daysLeft rappresenta il numero di giorni rimanenti alla fine del mese
            int daysLeft = Giorni_Del_Mese[mese-1] - giorno;
            if (daysLeft >= daysToAdd)
            {
                giorno += daysToAdd;
                daysToAdd = 0;
            }
            else
            {
                giorno = 1;
                daysToAdd -= daysLeft+1;

                //aggiungo un mese alla data,
                //incrementando l'anno se necessario
                mese += 1;
                if(mese > 12 ) {
                    mese = 1;
                    ++anno;
                }

            }
        } while(daysToAdd > 0);
    }

    //setta la data dell'oggetto chiamante alla data precedente a d
    public void previous_Date(Data d) {
        //se è il primo giorno del mese
        if(d.Giorno() == 1)
        {
                //mesi che hanno 30 giorni
                if(d.Mese() == 4|| d.Mese() == 6|| d.Mese() == 9|| d.Mese() == 11)
                {
                        giorno = 31;
                        mese = d.Mese() - 1;
                }
                //per Marzo, definire l'ultimo giorno di Febbraio
                else if(d.Mese()==3)
                {
                        //se l'anno è bisestile
                        if(d.Anno() % 4 == 0)
                                giorno = 29;
                        else
                                giorno = 28;
                        mese = d.Mese() - 1;
                }
                //per Gennaio, definire l'ultimo giorno di Dicembre
                else if(d.Mese()==1)
                {
                        giorno = 31;
                        mese = 12;
                        anno = d.Anno() - 1 ;
                }
                //Per Febbraio, definire l'ultimo giorno di Gennaio
                else if(d.Mese()==2)
                {
                        giorno = 31;
                        mese = d.Mese() -1;
                }
                //per gli altri mesi
                else
                {
                        giorno = 30;
                        mese = d.Mese() -1;
                }
        }
        //altri giorni del mese
        else
        {
                giorno = d.Giorno()-1;
        }
    }

    //sottrae due date e assegna il risultato dell'operazione all'oggetto chiamante
    public void subDates(Data d1, Data d2) {
		int[] increment = { 1, -2, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1 };

		int daysInc = 0;

		if (d1.Giorno() - d2.Giorno() < 0)
		{
			int month = d1.Mese() - 2; // -1 da zero, -1 mese precedente
			if (month < 0)
				month = 11; // Il precedente mese è Dicembre
			daysInc = increment[month];
			if ((month == 1) && (d1.Anno() % 4 == 0))
				daysInc++; // Incremento i giorni per l'anno bisestile
		}

		int total1 = d2.Anno()*360 + d2.Mese()*30 + d2.Giorno();
		int total2 = d1.Anno()*360 + d1.Mese()*30 + d1.Giorno();
		int diff = total1 - total2;
		int years = diff/360;
		int months = (diff - years*360)/30;
		int days = diff - years*360 - months*30 + daysInc;

		// Calcoli extra
		if (d2.Giorno() == 1 && d1.Giorno() == 31) {
			months--;
			days = 30;
		}

		setData(days, months, years);

    }

    public int diffGiorni(Data d1, Data d2, String tipo) {
        //cella[0] -> giorni; cella[1] -> lavorativi; cella[2] -> festivi
        //cella[3] -> sabati; cella[4] -> domeniche
        int[] days = new int[5];

        Data dt1 = new DataSett();
        dt1.setData(d1.Giorno(), d1.Mese(), d1.Anno());

        while(dt1.isNotEqual(d2)) {
            if(!dt1.Festivo())
                days[1]++;
            else
                days[2]++;

            if(dt1.toString() == "Sabato") days[3]++;
            if(dt1.toString() == "Domenica") days[4]++;

            dt1.addDays(1);
            days[0]++;
        }

        if(tipo == "l") return days[1]-days[4]; //ritorno i lavorativi (togliendo le domeniche)
        if(tipo == "f") return days[2]; //ritorno i festivi
        if(tipo == "s") return days[3]; //ritorno i sabati
        if(tipo == "d") return days[4]; //ritorno le domeniche
        return days[0]; //ritorno i giorni totali
    }
}
