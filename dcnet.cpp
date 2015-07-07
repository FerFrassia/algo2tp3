#include "dcnet.h"

using namespace aed2;


	DCNet::IniciarDCNet(Red& lared){
		red = Red(lared);

		Conj<Compu>::Iterador it CrearIt(lared.Computadoras());
		masEnviante = <it.Siguiente(),0)>
		
		CompYPaq = new DiccString<hostname>();

		while (it.HaySiguiente()){
			InfoCompu nuevainfo= new InfoCompu(); 

			dicc.definir((it.Siguiente()).hostname() , nuevainfo );
			it.Avanzar();
			}

		}

	~DCNet();

	&Red DCNet::Red(){
		return *red;
	}

	Lista<Compu> DCNet::CaminoRecorrido(const Paquete p){
		
		DiccString<hostname>::Iterador it(compYPaq);
		bool esta = false ;
		while(it.HaySiguiente() && !esta){
			if (((it.ValorActual()).paqyCam).def(Paquete)){
				esta = true;
				return ((it.ValorActual()).paqyCam).Obtener(Paquete);}
			it.Avanzar();
		}

		}


	Nat DCNet::CantidadEnviados(Compu c){
		return = (CompYPaq.Obtener(c.hostname)).enviados;
	}

	DiccRapido<Paquete>::ITClave DCNet::EnEspera(Compu c){

		DiccRapido<Paquete>::ITClave It((compYPaq.Obtener(c.hostname)).paqYCam)
		return It;
	}



	void DCNnet::CrearPaquete(Paquete p){
		DiccRapido<Nat> diccprio = compYPaq.Obtener((p.origen).hostname).masPriori;
		DiccRapido<Paquete> dicccam = compYPaq.Obtener((p.origen).hostname).paqYCam;

		if (! diccprio.def(p.prioridad)){
			Conj<Paquete> cj;
			cj.AgregarRapido(p);
			diccprio.definir(p.prioridad, cj);
		}else{
			Conj<Paquete> cj(diccprio.Obtener(p.prioridad));
			cj.AgregarRapido(p);
			diccprio.definir(p.prioridad, cj);
		}
		Lista<Compu> l;
		l.AgregarAtras(p.origen);
		dicccam.definir(p,l)
	}

	/*void DCNet::AvanzarSegundo(){
		Conj<Compu>::Iterador it(red.Computadoras());

		Lista l;

		while(it.HaySiguiente()){
			DiccRapido<Nat> diccprio = CompYPaq.Obtener((it.Siguiente()).hostname).masPriori;
			DiccRapido<Paquete> dicccam = CompYPaq.Obtener((it.Siguiente()).hostname).paqYCam;
			
			if(!diccprio.Vacio()){

				Conj<Compu>::Iterador it CrearIt(diccprio.Obtener(diccprio.ClaveMax()));
				Paquete paq = it.Siguiente();

			l.AgregarAdelante(tupla(paq,it.Siguiente(),dicccam.Obtener(paq)));
			diccprio.Obtener(diccprio.ClaveMax()).Eliminar(paq);
				if(Vacio(diccprio.Obtener(diccprio.ClaveMax()))){
					diccprio.Borrar(diccprio.ClaveMax());
				}
			dicccam.Borrar(paq);
			compYPaq.Obtener((it.Siguiente()).hostname).enviados ++;
			if (compYPaq.Obtener((it.Siguiente()).hostname).enviados) > masEnviante.enviados {
				masEnviante = tupla (it.Siguiente() , compYPaq.Obtener((it.Siguiente()).hostname).enviados);
			}


			}
		it.Avanzar();
		}
		Lista::Iterador itaux l.CrearIt();

		while(itaux.HaySiguiente()){
			Compu proxpc = 
		}







	}*/

	bool PaqueteEnTransito?(Paquete){
		Conj<Compu>::Iterador it = CrearIt(red.Computadoras());
		bool esta = false;
			while(it.HaySiguiente() && ! esta ){
				esta = ((compYPaq.Obtener((it.Siguiente()).hostname)).paqYcam).Def(Paquete);
			it.Avanzar();
		}

			return esta;
	}

	Compu LaQueMasEnvio(){
		return masEnviante.Compu;


	}
