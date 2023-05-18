import { useSelector } from 'react-redux'

import MapLayout from '@/components/Map/MapLayout.jsx'
import Window from '@/components/Window/Window'
import Menu from '@/components/Menu/Menu'
import PlaceList from '@/components/Place/PlaceList/PlaceList'
import Login from '@/components/Login/Login'
import Calendar from '@/components/Calendar/Calendar'
import PlacePageApi from '@/components/Place/PlacePage/PlacePageApi'
import Invite from '@/components/Invite/Invite'

export default function Place() {
	const position = useSelector(state => state.geoReducer.position)
	const pageNumber = useSelector(state => state.counterReducer.value)

	return (
		<MapLayout
			center={position}
			zoom={pageNumber == 6 || pageNumber == 7 ? 17 : 10}
		>
			<Window>
				{pageNumber === 3 && <Login />}
				{pageNumber === 4 && <PlaceList />}
				{pageNumber === 5 && <Calendar />}
				{pageNumber === 6 && <PlacePageApi />}
				{pageNumber === 7 && <Invite />}
				<Menu />
			</Window>
		</MapLayout>
	)
}
