# Aplicaciones Prácticas de las Funcionalidades del Sistema de Gestión Bancaria

1. **Banca Tradicional:**
   - *Descripción:* Gestión de cuentas bancarias de clientes, registro de transacciones, generación de informes financieros.
   - *Aplicación:* Utilizado en bancos físicos para administrar las operaciones diarias y mantener la integridad de los datos financieros.

2. **Aplicaciones FinTech:**
   - *Descripción:* Ofrecimiento de servicios bancarios digitales como cuentas bancarias móviles, transferencias de dinero y análisis financiero.
   - *Aplicación:* Plataformas móviles o en línea que permiten a los usuarios gestionar sus finanzas de manera conveniente y segura.

3. **Cooperativas de Crédito:**
   - *Descripción:* Gestionar cuentas de miembros, ofrecer servicios financieros personalizados para la comunidad.
   - *Aplicación:* Utilizado por cooperativas de crédito locales para proporcionar servicios bancarios a sus miembros y apoyar el desarrollo económico local.

4. **Gestión de Fondos:**
   - *Descripción:* Administrar carteras de inversión, realizar transacciones en nombre de los clientes, generar informes de rendimiento.
   - *Aplicación:* Empresas de gestión de activos que utilizan este sistema para administrar inversiones y proporcionar información detallada sobre el rendimiento de las inversiones a los clientes.

5. **Administración de Préstamos:**
   - *Descripción:* Gestionar detalles de préstamos, seguimiento de pagos, generación de informes sobre el estado de los préstamos.
   - *Aplicación:* Instituciones financieras que ofrecen préstamos utilizan este sistema para administrar los detalles de los préstamos y garantizar un seguimiento preciso de los pagos de los clientes.

6. **Contabilidad Empresarial:**
   - *Descripción:* Gestión de finanzas internas, seguimiento de ingresos y gastos, generación de informes financieros.
   - *Aplicación:* Empresas que utilizan este sistema para llevar registros financieros, realizar seguimiento de transacciones comerciales y generar informes para la toma de decisiones estratégicas.

# Descripción Técnica del Sistema de Gestión Bancaria

## 1. Implementación en Lenguaje C:
   - **Lenguaje de Programación:** El sistema de gestión bancaria fue implementado utilizando el lenguaje de programación C.
   - **Razones de la Elección:** C es un lenguaje ampliamente utilizado en el desarrollo de sistemas de bajo nivel y aplicaciones de alto rendimiento. Ofrece un control preciso sobre los recursos del sistema y es ideal para aplicaciones que requieren un alto grado de eficiencia y velocidad.

## 2. Uso de Hilos y Mutex:
   - **Hilos (Threads):** El sistema hace uso de hilos para realizar operaciones de carga de datos de manera concurrente, lo que mejora la eficiencia y reduce el tiempo de ejecución.
   - **Mutex (Mutexes):** Se utiliza un mutex para garantizar la exclusión mutua al acceder a recursos compartidos, como archivos y estructuras de datos. Esto previene condiciones de carrera y garantiza la consistencia de los datos durante las operaciones concurrentes.
   - **Beneficios:** La implementación de hilos y mutexes permite que el sistema maneje múltiples tareas simultáneamente de manera segura y eficiente, lo que mejora el rendimiento y la capacidad de respuesta del sistema.


# Funcionalidades del Sistema de Gestión Bancaria

## Carga de Usuarios
- Permite cargar información de usuarios desde un archivo CSV.
- La información incluye el número de cuenta, nombre y saldo.

## Carga de Operaciones
- Carga operaciones bancarias desde un archivo CSV.
- Las operaciones pueden ser depósitos, retiros o transferencias entre cuentas.
- Cada operación incluye detalles como el tipo de operación, número de cuenta origen y destino, y el monto.

## Operaciones Individuales
- Ofrece un menú para realizar operaciones individuales como depósitos, retiros y transferencias.
- Las operaciones se realizan sobre las cuentas cargadas previamente.

## Verificación de Usuarios
- Realiza una serie de verificaciones sobre los datos de usuarios cargados.
- Busca errores como números de cuenta no positivos, saldos negativos y números de cuenta duplicados.
- Genera un archivo de registro de errores para la carga de usuarios.

## Verificación de Operaciones
- Realiza verificaciones similares a las de usuarios sobre las operaciones cargadas.
- Busca errores como números de cuenta inexistentes, montos negativos y tipos de operaciones inválidos.
- Genera un archivo de registro de errores para la carga de operaciones.

## Reporte de Cuentas
- Genera un archivo CSV que contiene la información de las cuentas cargadas.
- Útil para mantener un registro actualizado de las cuentas y sus saldos.
