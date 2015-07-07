#ifndef DRIVER_H_
#define DRIVER_H_

#include "Tipos.h"
#include "aed2/TiposBasicos.h"
#include "aed2/Vector.h"
#include "ArbolSintactico.h"

//#include ...

namespace aed2 {

class Driver
{
	public:

    Driver(const Conj<Estacion>& estacionesIniciales);

    ~Driver();

    /// Observadores Mapa //////////////////////////////////////////////////////////

    Nat CantidadEstaciones() const;

    // PRE: i < #estaciones()
    Estacion IesimaEstacion(Nat i) const;

    // PRE: e \in estaciones()
    Nat CantidadDeSendasParaEstacion(const Estacion& e) const;

    // PRE: e \in estaciones() \and i < # {e2:Estacion | conectadas?(e,e2)}
    Estacion IesimaEstacionDeSenda(const Estacion& e, Nat i) const;

    // PRE: e \in estaciones() \and i < # {e2:Estacion | conectadas?(e,e2)}
    Restriccion IesimaRestriccionDeSenda(const Estacion& e1, Nat i) const;

    /// Armado Mapa ////////////////////////////////////////////////////////////////

    /*******************************************************
     * VER DESCRIPCION DE LAS RESTRICCIONES EN Tipos.h !!! *
     *******************************************************/

    // PRE: e1 \in estaciones() \and e2 \in estaciones() \and \not conectadas?(e1,e2)
    void AgregarSenda(const Estacion& e1, const Estacion& e2, Restriccion r);

    /// Observadores Ciudad //////////////////////////////////////////////////////////////

    Nat CantidadRobotsActivos() const;

    /// PRE: i < #robots()
    RUR IesimoRobotActivo(Nat i) const;

    /// PRE: i < #robots()
    Estacion EstacionActualIesimoRobotActivo(Nat i) const;

    /// PRE: i < #robots()
    Conj<Caracteristica> CaracteristicasIesimoRobotActivo(Nat i) const;

    /// PRE: i < #robots()
    Nat CantInfraccionesIesimoRobotActivo(Nat i) const;

    /// PRE: (\exists r:RUR) r \in robots() \and #infracciones(r) > 0
    RUR ElMasInfractor() const;

    /// Acciones Ciudad ////////////////////////////////////////////////////////////
    /// Al empezar a usar estas operaciones se asume que ya no se agregan sendas nuevas

    /// PRE: estacionInicial \in estaciones()
    void Entrar(const Conj<Caracteristica> & cs, const Estacion& estacionInicial);

    /// PRE: robot \in robots() \and destino \in estaciones()
    void Mover(RUR robot, const Estacion& destino);

    /// PRE: e \in estaciones()
    void Inspeccion(const Estacion & e);

	private:
        struct Senda {
            const Estacion e1;
            const Estacion e2;
            ArbolSintactico* expr;

            Senda(const Estacion& e1, const Estacion& e2, ArbolSintactico* expr):
                e1(e1), e2(e2), expr(expr) {};

            Senda(const Senda& otra): e1(otra.e1), e2(otra.e2), expr(otra.expr) {};
        };

        struct Robot {
            RUR rur;
            bool activo;
            Estacion estacionActual;
            Nat infracciones;
            Conj<Caracteristica> caracteristicas;
            Dicc<Estacion, Dicc<Estacion, bool> > sendasInfractoras;
            // Iterador simulado de la cola de prioridad con un conjunto. Se omiten las # infracciones
            typename Conj<RUR>::Iterador itColaActual;

            Robot(RUR rur, const Estacion& estacionInicial, const Conj<Caracteristica>& cs, typename Conj<RUR>::Iterador itColaActual):
                rur(rur), activo(true),
                estacionActual(estacionInicial),
                infracciones(0), caracteristicas(cs), itColaActual(itColaActual) {}

        };  

        // Esto seria el mapa {
        const Conj<Estacion>& estaciones;
        Conj<Senda> sendas;
        // } Mapa

        Vector<Robot> robots;
        Dicc<Estacion, Conj<RUR> > robotsEnEstaciones;

        // Simulacion del iterador de elementos no borrados
        const Robot& _IesimoRobotActivo(Nat i) const {
            Nat actual = 0;
            for(typename Vector<Robot>::const_Iterador it = robots.CrearIt(); it.HaySiguiente(); it.Avanzar()) {
                if(it.Siguiente().activo && actual == i) {
                    return it.Siguiente();
                }

                if(it.Siguiente().activo) {
                    actual++;
                }
            }
            assert(false);
        }

}; // class Driver


} // namespace aed2

#endif // DRIVER_H_
