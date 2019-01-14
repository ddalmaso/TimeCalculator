import java.lang.*;
import java.text.SimpleDateFormat;

public class DataOra extends Data {
    private int ore;        //0 - 23
    private int minuti;     //0 - 59
    private int secondi;    //0 - 59

    //imposto l'orario corrente di default
    public DataOra() {
        super(); //invoco il costruttore di default della classe Data che inizializza alla data corrente
        String hours = new SimpleDateFormat("HH").format(new java.util.Date());
        ore = Integer.parseInt(hours);
        String minutes = new SimpleDateFormat("mm").format(new java.util.Date());
        minuti = Integer.parseInt(minutes);
        String seconds = new SimpleDateFormat("ss").format(new java.util.Date());
        secondi = Integer.parseInt(seconds);
    }

    public DataOra(int hh, int mm, int ss, int g, int m, int a) throws IllegalArgumentException {
        super(g, m, a);
        if(hh < 0 || hh > 23 || mm < 0 || mm > 59 || ss < 0 || ss > 59)
            throw new IllegalArgumentException();
        ore = hh;
        minuti = mm;
        secondi = ss;
    }

    public DataOra(int h, int m, int s) throws IllegalArgumentException
    {
        super();
        if(h < 0 || h > 23 || m < 0 || m > 59 || s < 0 || s > 59)
            throw new IllegalArgumentException();
        ore = h;
        minuti = m;
        secondi = s;
    }


    public int Ore() { return ore; }

    public void setOre(int o) { ore = o; }

    public int Minuti() { return minuti; }

    public void setMinuti(int m) { minuti = m; }

    public int Secondi() { return secondi; }

    public void setSecondi(int s) { secondi = s; }

    public String toString() {  //overrides
        StringBuilder s = new StringBuilder();
        if (ore < 10) s.append("0");
        s.append(String.valueOf(ore));
        s.append(":");
        if (minuti < 10) s.append("0");
        s.append(String.valueOf(minuti));
        s.append(":");
        if(secondi < 10) s.append("0");
        s.append(String.valueOf(secondi));
        return s.toString();
    }

    public int orarioToSec() {
        return ore*3600 + minuti*60 + secondi;
    }

    public boolean isEqual(Object obj) {
        if(obj instanceof DataOra){
            DataOra time = (DataOra) obj;
            return orarioToSec() == time.orarioToSec();
        }
        return false;
    }

    public boolean isNotEqual(Object obj) {
        return !(this.isEqual(obj));
    }

    public boolean isLesser(DataOra r) {
        return orarioToSec() < r.orarioToSec();
    }

    //somma due orari e assegna il risultato dell'operazione all'oggetto chiamante
    public void sumTimes(DataOra r, DataOra s) {
		int hours, minutes, seconds;
		int sum;
		sum = (r.Ore() + s.Ore())*3600 + (r.Minuti() + s.Minuti())*60 + r.Secondi() + s.Secondi();
		seconds = sum % 60;
		sum = sum / 60;
		minutes = sum % 60;
		hours = sum / 60;
		setOre(hours); setMinuti(minutes); setSecondi(seconds);
    }

    //sottrae l'orario s da r e assegna il risultato dell'operazione all'oggetto chiamante
    public void subTimes(DataOra r, DataOra s) {
        if(r.isEqual(s))
            ore = minuti = secondi = 0;
        else
        {
            if(r.Secondi() < s.Secondi()) {
                r.setSecondi(r.Secondi() + 60);
                if(r.Minuti() == 0) r.setMinuti(59);
                else
                    r.setMinuti(r.Minuti() - 1);
            }
            this.setSecondi(r.Secondi() - s.Secondi());

            if(r.Minuti() < s.Minuti()) {
                r.setMinuti(r.Minuti() + 60);
                if(r.Ore() == 0) r.setOre(23);
                else
                    r.setOre(r.Ore() - 1);
            }
            this.setMinuti(r.Minuti() - s.Minuti());

            if(r.Ore() < s.Ore())
                r.setOre(r.Ore() + 24);
            else
                this.setOre(r.Ore() - s.Ore());
        }
    }
}
