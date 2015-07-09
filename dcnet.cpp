#include "dcnet.h"

using namespace aed2;


	DCNet::DCNet(Red& lared){
		red = *new Red(lared);

		Conj<Compu>::Iterador it = Iterador(lared.Computadoras());
		masEnviante = new tuple<it.Siguiente(), 0>;
		
		compYPaq = new DiccString<Hostname>();

		while (it.HaySiguiente()){
			DCNet::InfoCompu nuevainfo= new InfoCompu(); 

			compYPaq.definir((it.Siguiente()).hostname() , nuevainfo );
			it.Avanzar();
			}

		}

	DCNet::~DCNet(){

		delete red;
		delete compYPaq;
		delete masEnviante;


	}

	Red& DCNet::Red(){
		return *red;
	}

	Lista<Compu> DCNet::CaminoRecorrido(const Paquete p){
		
		DiccString<Hostname>::Iterador it = Iterador(compYPaq);
		bool esta = false ;
		while(it.HaySiguiente() && !esta){
			if (((it.ValorActual()).paqyCam).Def(Paquete)){
				esta = true;
				return ((it.ValorActual()).paqyCam).Obtener(Paquete);}
			it.Avanzar();
		}

	}


	Nat DCNet::CantidadEnviados(Compu c){
		return = (compYPaq.obtener(c.hostname)).enviados;
	}

	DiccRapido<Paquete>::ITClave DCNet::EnEspera(Compu c){

		DiccRapido<Paquete>::ITClave It((compYPaq.obtener(c.hostname)).paqYCam)
		return It;
	}



	void DCNnet::CrearPaquete(Paquete p){
		DiccRapido<Nat> diccprio = compYPaq.obtener((p.origen).hostname).masPriori;
		DiccRapido<Paquete> dicccam = compYPaq.obtener((p.origen).hostname).paqYCam;

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
		Conj<Compu>::Iterador it(red.Computadoras());

		Lista l;

		while(it.HaySiguiente()){
			DiccRapido<Nat> diccprio = CompYPaq.Obtener((it.Siguiente()).hostname).masPriori;
			DiccRapido<Paquete> dicccam = CompYPaq.Obtener((it.Siguiente()).hostname).paqYCam;
			
			if(!diccprio.Vacio()){

				Conj<Compu>::Iterador it CrearIt(diccprio.Obtener(diccprio.ClaveMax()));
				Paquete paq = it.Siguiente();

			l.AgregarAdelante(tuple<paq,it.Siguiente(),dicccam.Obtener(paq)>);
			//el componente 0 de la tupla es el paquete, 
			//el componente 1 es la computadora en la que esta
			//el componente 2 es la lista de computadoras por la que ya paso
			diccprio.Obtener(diccprio.ClaveMax()).Eliminar(paq);
				if(Vacio(diccprio.Obtener(diccprio.ClaveMax()))){
					diccprio.Borrar(diccprio.ClaveMax());
				}
			dicccam.Borrar(paq);
			get<1>(compYPaq.Obtener((it.Siguiente()).hostname)) ++;
			if (get<1>(compYPaq.Obtener((it.Siguiente()).hostname)) > get<1>(masEnviante) {
				masEnviante = tuple <it.Siguiente() , compYPaq.Obtener((it.Siguiente()).hostname).enviados>;
			}


			}
		it.Avanzar();
		}
		Lista::Iterador itaux = l.CrearIt();

		while(itaux.HaySiguiente()){
			Compu proxpc = ((red.CaminosMinimos(get<1>(itaux.Siguiente()),(get<0>(itaux.Siguiente())).destino)).Siguiente()).Primero();
			DiccRapido<Nat> diccprio = (CompYPaq.Obtener(proxpc.hostname)).masPriori;
			DiccRapido<Paquete> dicccam = (CompYPaq.Obtener(proxpc.hostname)).paqYCam;
			
			if (proxpc != get<0>(itaux.Siguiente()).destino){
				if (diccprio.Def((itaux.Siguiente()).prioridad)){
					Conj<Paquete> mismaPrio = (diccprio.Obtener(get<0>((itaux.Siguiente())).prioridad)).Agregar(get<0>(itaux.Siguiente()));
					diccprio.Definir(get<0>(itaux.Siguiente()).prioridad,mismaPrio);
				}else{
					Conj<Paquete> conjvacio;
					diccprio.Definir(get<0>(itaux.Siguiente()).prioridad,conjvacio.Agregar(get<0>(itaux.Siguiente())));
				}
			}else{
				dicccam.Definir(get<0>(itaux.Siguiente()),get<2>(itaux.Siguiente()).AgregarAtras(proxpc));
			}
			itaux.Avanzar();
		}
	}

	bool DCNet::PaqueteEnTransito(Paquete){
		Conj<Compu>::Iterador it = Iterador(red.Computadoras());
		bool esta = false;
			while(it.HaySiguiente() && ! esta ){
				esta = ((compYPaq.Obtener((it.Siguiente()).hostname)).paqYcam).Def(Paquete);
			it.Avanzar();
		}

			return esta;
	}

	Compu DCNet::LaQueMasEnvio(){
		return get<0>(masEnviante);


	}
