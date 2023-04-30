import React from 'react'
import { YMaps, Map, Placemark } from '@pbe/react-yandex-maps'

export default function MapLayout({ children, center, zoom }) {
	return (
		<YMaps>
			<Map width='100vw' height='100vh' state={{ center, zoom }}>
				<Placemark geometry={center} />
			</Map>
			{children}
		</YMaps>
	)
}
