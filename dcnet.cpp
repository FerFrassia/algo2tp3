#include "dcnet.h"

using namespace aed2;


	/*Este Struct solamente se utiliza en la funcion "Avanzar Segundo" y es requerido para poder guardar la informacion
  	de los paquetes a mover.*/
	struct InfoPaquete{

		Paquete paque;
		Compu compuAnt;
		Lista<Compu> camReco;

		InfoPaquete(Paquete p, Compu c, Lista<Compu> cr): paque(p),compuAnt(c), camReco(cr) {};
	};

	DCNet::DCNet(Red& lared){
		red = new Red(lared);

		Conj<Compu>::Iterador it = lared.Computadoras();
		masEnviante = new masEnvio( it.Siguiente(), 0);
		
		compYPaq = new DiccString<Hostname>();

		while (it.HaySiguiente()){
			DCNet::InfoCompu *nuevainfo= new InfoCompu(); 

			compYPaq->definir(((it.Siguiente()).hostname) , nuevainfo* );
			it.Avanzar();
			}

		}

	DCNet::~DCNet(){

		delete red;
		delete compYPaq;
		delete masEnviante;


	}

	Red DCNet::DameRed(){
		return *red;
	}

	Lista<Compu> DCNet::CaminoRecorrido(const Paquete p){
		
		DiccString<Hostname>::Iterador it = Iterador(compYPaq);
		bool esta = false ;
		Lista<Compu> res;
		while(it.HaySiguiente() && !esta){
			if (((it.valorActual())->paqyCam).Def(Paquete)){
				esta = true;
				res = ((it.valorActual()).paqyCam).Obtener(Paquete);
			}
			it.avanzar();
		}
		return res;
	}


	Nat DCNet::CantidadEnviados(Compu c){
		return (compYPaq.obtener(c.hostname))->enviados;
	}

	DiccRapido<Paquete,Lista <Compu> >::ITClave DCNet::EnEspera(Compu c){

		DiccRapido<Paquete,Lista <Compu> >::ITClave It((compYPaq.obtener(c.hostname)) -> paqYCam);
		return It;
	}



	void DCNet::CrearPaquete(Paquete p){
		DiccRapido<Nat,Conj<Paquete> > diccprio = compYPaq.obtener((p.origen).hostname)->masPriori;
		DiccRapido<Paquete,Lista <Compu> > dicccam = compYPaq.obtener((p.origen).hostname)->paqYCam;

		if (! diccprio.Def(p.prioridad)){
			Conj<Paquete> cj;
			cj.AgregarRapido(p);
			diccprio.Definir(p.prioridad, cj);
		}else{
			Conj<Paquete> cj(diccprio.Obtener(p.prioridad));
			cj.AgregarRapido(p);
			diccprio.Definir(p.prioridad, cj);
		}
		Lista<Compu> l;
		l.AgregarAtras(p.origen);
		dicccam.Definir(p,l);
	}

	void DCNet::AvanzarSegundo(){
		Conj<Compu>::Iterador it = red.Computadoras();

		Lista<InfoPaquete> l;

		while(it.HaySiguiente()){
			DiccRapido<Nat,Conj<Paquete> > diccprio = compYPaq.Obtener((it.Siguiente()).hostname).masPriori;
			DiccRapido<Paquete,Lista <Compu> > dicccam = compYPaq.Obtener((it.Siguiente()).hostname).paqYCam;
			
			if(!diccprio.Vacio()){

				Paquete paq = (diccprio.Obtener(diccprio.ClaveMax())).DameUno();
				

				l.AgregarAdelante(InfoPaquete(paq,it.Siguiente(),dicccam.Obtener(paq)));
			
				diccprio.Obtener(diccprio.ClaveMax()).Eliminar(paq);
				if((diccprio.Obtener(diccprio.ClaveMax())).EsVacio()){
					diccprio.Borrar(diccprio.ClaveMax());
				}
				dicccam.Borrar(paq);
			(compYPaq.Obtener((it.Siguiente()).hostname)).paque ++;
			if ((compYPaq.Obtener((it.Siguiente()).hostname)).enviados > masEnviante.enviados) {
				masEnviante = masEnvio(it.Siguiente() , compYPaq.Obtener((it.Siguiente()).hostname).enviados);
			}


			}
			it.Avanzar();
		}
		Lista<InfoPaquete>::Iterador itaux = l.CrearIt();

		while(itaux.HaySiguiente()){
			Compu proxpc = ((red.CaminosMinimos(((itaux.Siguiente()).compuAnt),(((itaux.Siguiente()).paque).destino))).Siguiente()).Primero();
			DiccRapido<Nat,Conj<Paquete> > diccprio = (compYPaq.Obtener(proxpc.hostname)).masPriori;
			DiccRapido<Paquete,Lista <Compu> > dicccam = (compYPaq.Obtener(proxpc.hostname)).paqYCam;
			
			if (proxpc != ((itaux.Siguiente()).paque).destino){
				if (diccprio.Def(((itaux.Siguiente()).paque).prioridad)){
					Conj<Paquete> mismaPrio = (diccprio.Obtener(((itaux.Siguiente()).paque).prioridad)).Agregar((itaux.Siguiente()).paque);
					diccprio.Definir(((itaux.Siguiente()).paque).prioridad,mismaPrio);
				}else{
					Conj<Paquete> conjvacio;
					diccprio.Definir(((itaux.Siguiente()).paque).prioridad,conjvacio.Agregar((itaux.Siguiente()).paque));
				}
			}else{
				dicccam.Definir((itaux.Siguiente()).paque,((itaux.Siguiente()).camReco).AgregarAtras(proxpc));
			}
			itaux.Avanzar();
		}
	} 

	bool DCNet::PaqueteEnTransito(Paquete){
		Conj<Compu>::Iterador it = red.Computadoras();
		bool esta = false;
			while(it.HaySiguiente() && ! esta ){
				esta = ((compYPaq.Obtener((it.Siguiente()).hostname)).paqYcam).Def(Paquete);
			it.Avanzar();
		}
		return esta;
		}

	Compu DCNet::LaQueMasEnvio(){
		return masEnviante.comp;
	}

